#include "HT.h"


namespace HT
{
	HtHandle::HtHandle()
	{
		this->capacity = 0;
		this->SnapchotIntervalInSecond = 0;
		this->maxKeyLength = 0;
		this->maxPayLoadLength = 0;
		ZeroMemory(this->fileName, sizeof(this->fileName)); //like memset but only nulls out the memory
		this->file = NULL;
		this->fileMapping = NULL;
		this->addr = NULL;
		ZeroMemory(this->lastErrorMessage, sizeof(this->lastErrorMessage));
		this->lastSnaptime = 0;

		this->count = 0;
	}

	HtHandle::HtHandle(int capacity, int secSnapshotInterval, int maxKeyLength, int maxPayloadLength, const wchar_t* fileName) : HtHandle()
	{
		this->capacity = capacity;
		this->SnapchotIntervalInSecond = secSnapshotInterval;
		this->maxKeyLength = maxKeyLength;
		this->maxPayLoadLength = maxPayloadLength;
		memcpy(this->fileName, fileName, sizeof(this->fileName));
	}

	HtHandle* create(
		int	  capacity,				
		int   secSnapshotInterval,		
		int   maxKeyLength,             
		int   maxPayloadLength,			
		const wchar_t* fileName)
		{
		HANDLE hf = CreateFile(
			fileName,
			GENERIC_WRITE | GENERIC_READ, //access mode
			NULL, //share mode
			NULL, //security attributes
			OPEN_ALWAYS, //how to act
			FILE_ATTRIBUTE_NORMAL, //FILE_ATTRIBUTE_TEMPORARY
			NULL); //file template handle
		if (hf == INVALID_HANDLE_VALUE)
			throw "create or open file failed";

		int sizeMap = sizeof(HtHandle) + getSizeElement(maxKeyLength, maxPayloadLength) * capacity;
		
		HANDLE hm = CreateFileMapping(
			hf, //file handle
			NULL, //security attributes
			PAGE_READWRITE, //protection
			0, //high-order DWORD of size
			sizeMap, //size of mapping
			fileName);
		if (!hm)
			throw "create File Mapping failed";

		LPVOID lp = MapViewOfFile(
			hm, //handle to map object
			FILE_MAP_ALL_ACCESS, //access mode
			0, //high-order DWORD of offset
			0, //low-order DWORD of offset
			0); //number of bytes to map
		if (!lp)
			return NULL;

		ZeroMemory(lp, sizeMap);

		HtHandle* htHandle = new(lp) HtHandle(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, fileName);
		htHandle->file = hf;
		htHandle->fileMapping = hm;
		htHandle->addr = lp;
		htHandle->lastSnaptime = time(NULL);
		htHandle->mutex = CreateMutex(
			NULL, //security attributes
			FALSE, //initial owner
			fileName); //name of mutex object
		runSnapchotTimer(htHandle);

		return htHandle;
	}


	BOOL runSnapchotTimer(HtHandle* const htHandle)
	{
		htHandle->snapchotTimer = CreateWaitableTimer(
			0, //security attributes
			FALSE, //true - manual reset, false - auto reset
			0); //timer name
		LARGE_INTEGER Li{}; //64 bit number
		Li.QuadPart = -(SECOND * htHandle->SnapchotIntervalInSecond); //time to wait in 100-nanosecond intervals (first time run immediately and then every ... seconds)
		SetWaitableTimer(
			htHandle->snapchotTimer, //handle to timer object
			&Li, //time to wait
			1, //periodic (time to count)
			snapAsync, //calling function
			htHandle, //parameter to the function
			FALSE); //true - timer is reset, false - timer is not reset

		return true;
	}

	const char* writeLastError(HtHandle* const htHandle, const char* msg)
	{
		memcpy(htHandle->lastErrorMessage, msg, sizeof(htHandle->lastErrorMessage));
		return htHandle->lastErrorMessage;
	}

	const char* getLastError  
	(
		const HtHandle* htHandle)
	{
		return htHandle->lastErrorMessage;
	}

	void CALLBACK snapAsync(LPVOID prm, DWORD, DWORD) //prm - parameter to the function
	{
		HtHandle* htHandle = (HtHandle*)prm;
		if (snap(htHandle))
			std::cout << "-- spanshotAsync success" << std::endl;
	}

	BOOL snap //run Snapshot
	(
		HtHandle* htHandle) // manage HT (File, FileMapping)
	{
		WaitForSingleObject(htHandle->mutex, INFINITE); //INFINITE - wait forever

		if (!FlushViewOfFile(htHandle->addr, NULL)) //NULL - all file and this function flushes the buffers of a specified file to disk
		{
			writeLastError(htHandle, "-- FlushViewOfFile error");
			ReleaseMutex(htHandle->mutex);
			return false;
		}
		
		htHandle->lastSnaptime = time(NULL);
		ReleaseMutex(htHandle->mutex);
		return true;
	}

	BOOL insert
	(
		HtHandle* HtHandle, // manage HT (File, FileMapping)
		const Element* element //element to insert
	)
	{
		HT::Element* hte = HT::get(HtHandle, element);
		if (hte)
		{
			throw "insert: element already exist((";
		}

		if (HtHandle->count >= HtHandle->capacity)
		{
			writeLastError(HtHandle, "-- HT is full");
			return false;
		};

		WaitForSingleObject(HtHandle->mutex, INFINITE);
		
		int freeIndex = findFreeIndex(HtHandle, element);

		writeToMemory(HtHandle, element, freeIndex);
		HtHandle->count++;
		ReleaseMutex(HtHandle->mutex);

		return true;
	}

	int findFreeIndex
	(
		const HtHandle* HtHandle, // manage HT (File, FileMapping)
		const Element* element //element to insert
	)
	{
		int index = hash((char*)element->key, HtHandle->capacity);

		Element* foundElement = new Element();

		do
		{
			if (index >= HtHandle->capacity)
			{
				index = -1;
				break;
			}

			readFromMemory(HtHandle, foundElement, index);
			index = nextHash(index, (char*)element->key, HtHandle->capacity);
		} while (
			foundElement->keyLength != 0 &&
			foundElement->payloadLength != 0);

		delete foundElement;
		return index - 1;
	}

	int hash(const char* key, int capacity)
	{
		unsigned long i = 0;
		for (int j = 0; key[j]; j++)
			i += key[j];
		return i % capacity;
	}

	int nextHash(int currentHash, const char* key, int capacity)
	{
		return ++currentHash;
	}

	Element* readFromMemory(
		const HtHandle* htHandle,
		Element* const element,
		int index
	)
	{
		LPVOID lp = htHandle->addr; //pointer to start position

		lp = (HtHandle*)lp + 1; //skip HtHandle
		lp = (byte*)lp + getSizeElement(htHandle->maxKeyLength, htHandle->maxPayLoadLength) * index; //skip elements before index

		element->key = lp; //set key
		lp = (byte*)lp + htHandle->maxKeyLength; //skip key
		element->keyLength = *(int*)lp; //set key length
		lp = (int*)lp + 1; //skip key length
		element->payload = lp; //set payload
		lp = (byte*)lp + htHandle->maxPayLoadLength; //skip payload
		element->payloadLength = *(int*)lp; //set payload length

		return element;
	}

	BOOL writeToMemory(
		const HtHandle* const htHandle,
		const Element* const element,
		int index
	)
	{
		LPVOID lp = htHandle->addr; //pointer to start position

		lp = (HtHandle*)lp + 1; //skip HtHandle
		lp = (byte*)lp + getSizeElement(htHandle->maxKeyLength, htHandle->maxPayLoadLength) * index; //skip elements before index

		memcpy(lp, element->key, htHandle->maxKeyLength); //set key
		lp = (byte*)lp + htHandle->maxKeyLength; //skip key

		memcpy(lp, &element->keyLength, sizeof(int)); //set key length
		lp = (int*)lp + 1; //skip key length

		memcpy(lp, element->payload, htHandle->maxPayLoadLength); //set payload
		lp = (byte*)lp + htHandle->maxPayLoadLength; //skip payload

		memcpy(lp, &element->payloadLength, sizeof(int)); //set payload length

		return true;
	}

	Element* get
	(
		HtHandle* htHandle, // manage HT (File, FileMapping)
		const Element* element //element to get
	)
	{
		int index = findIndex(htHandle, element);

		if (index < 0)
		{
			writeLastError(htHandle, "-- element not found(GET)((((((");
			return NULL;
		}

		Element* foundElement = new Element();
		readFromMemory(htHandle, foundElement, index);
		return foundElement;
	}

	int findIndex(
		const HtHandle* htHandle, // manage HT (File, FileMapping)
		const Element* element //element to get
	)
	{
		int index = hash((char*)element->key, htHandle->capacity);

		Element* foundElement = new Element();

		do
		{
			if(index >= htHandle->capacity)
			{
				index = -1;
				break;
			}
			readFromMemory(htHandle, foundElement, index);
			index = nextHash(index, (char*)element->key, htHandle->capacity);

		} while (memcmp(foundElement->key, element->key, element->keyLength) != 0);
		
		delete foundElement;
		return index - 1;
	}

	void print(const Element* element)
	{
		std::cout << "Element:" << std::endl;
		std::cout << "{" << std::endl;
		std::cout << "\t\"key\": \"" << (char*)element->key << "\"," << std::endl;
		std::cout << "\t\"keyLength\": " << element->keyLength << "," << std::endl;
		std::cout << "\t\"payload\": \"" << (char*)element->payload << "\"," << std::endl;
		std::cout << "\t\"payloadLength\": " << element->payloadLength << std::endl;
		std::cout << "}" << std::endl;
	};

	BOOL update //change element in storage
	(
		HtHandle* htHandle, // manage HT (File, FileMapping)
		const Element* oldElement, //element to update
		const void* newPayload,  
		int newPayloadLength)  
	{
		WaitForSingleObject(htHandle->mutex, INFINITE);

		int index = findIndex(htHandle, oldElement);
		if (index < 0)
		{
			writeLastError(htHandle, "-- not found element (UPDATE)((((((((");
			ReleaseMutex(htHandle->mutex);
			return false;
		}

		Element* updateElement = new Element(oldElement, newPayload, newPayloadLength);
		writeToMemory(htHandle, updateElement, index);
		ReleaseMutex(htHandle->mutex);

		return true;
	};

	BOOL remove //remove element from storage
	(
		HtHandle* HtHandle, // manage HT (File, FileMapping)
		const Element* element //element to remove
	)
	{
		WaitForSingleObject(HtHandle->mutex, INFINITE);
		int index = findIndex(HtHandle, element);

		if (index < 0)
		{
			writeLastError(HtHandle, "-- not found element (REMOVE)((((((((((");
			ReleaseMutex(HtHandle->mutex);
			return false;
		}

		clearMemoryByIndex(HtHandle, index);
		HtHandle->count--;
		ReleaseMutex(HtHandle->mutex);

		return true;
	};

	BOOL clearMemoryByIndex(const HtHandle* const htHandle, int index)
	{
		LPVOID lp = htHandle->addr; //pointer to start position
		int sizeElement = getSizeElement(htHandle->maxKeyLength, htHandle->maxPayLoadLength);

		lp = (HtHandle*)lp + 1; //skip HtHandle
		lp = (byte*)lp + sizeElement * index; //skip elements before index

		ZeroMemory(lp, sizeElement); //clear memory

		return true;
	}

	BOOL close
	(
		const HtHandle* htHandle // manage HT (File, FileMapping)
	)
	{
		HANDLE hf = htHandle->file;
		HANDLE hm = htHandle->fileMapping;

		if (!CancelWaitableTimer(htHandle->snapchotTimer)) //cancel snapshotTimer
			throw "cancel snapshotTimer failed";
		if (!UnmapViewOfFile(htHandle->addr))	//unmap view of file
			throw "unmapping view failed";
		if (!CloseHandle(hm)) //close File Mapping
			throw "close File Mapping failed";
		if (hf != NULL)
			if (!CloseHandle(hf)) 
				throw "close File failed";

		return true;
	};

	HtHandle* open
	(
		const wchar_t* fileName //name of file
	)
	{
		HANDLE hf = CreateFile(
			fileName,
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hf == INVALID_HANDLE_VALUE)
			return NULL;

		HANDLE hm = CreateFileMapping(
			hf,
			NULL,
			PAGE_READWRITE,
			0, 0,
			fileName);
		if (!hm)
			return NULL;

		LPVOID lp = MapViewOfFile(
			hm,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (!lp)
			return NULL;

		HtHandle* htHandle = (HtHandle*)lp;
		htHandle->file = hf;
		htHandle->fileMapping = hm;
		htHandle->addr = lp;
		htHandle->lastSnaptime = time(NULL);

		if (htHandle == NULL)
		{
			return NULL;
		}

		runSnapchotTimer(htHandle);
		return htHandle;
	};
}