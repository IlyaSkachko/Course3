#pragma once
#include "Element.h"
#include <Windows.h>
#include <iostream>

#define SECOND 10000000

namespace HT		//HT API 
{
	struct HtHandle //блок управления HT 
	{
		HtHandle();
		HtHandle(int capacity, int SnapchotIntervalInSecond, int maxKeyLength, int maxPayLoadLength, const wchar_t* fileName);
		int capacity; //count of elements
		int SnapchotIntervalInSecond; //interval for update in seconds
		int maxKeyLength; //max key length
		int maxPayLoadLength; //max PayLoadLength
		wchar_t fileName[512]; //file name
		HANDLE file; //file handle !=0 if file is open
		HANDLE fileMapping; //mapping file handle !=0 if mapping is create
		LPVOID addr; // Addr != NULL, if mapview if complete
		char lastErrorMessage[512]; //last error message or 0x00
		time_t lastSnaptime; //date of last snap (time())
		int count; //current count of elements in HT
		HANDLE snapchotTimer; //timer for snapchot
		HANDLE mutex; //this is mutex for synchronization differenr HtHandle copies (like semaphor or critical section)
	};

	HtHandle* create //create HT 
	(
		int capacity, //storage capacity
		int maxSnapInterval, //frequency of storage in sec
		int maxKeyLength, //max size of key
		int maxPayLoadLen, //max size of data
		const wchar_t* filename //file name
	); // != NULL - success complete

	HtHandle* open //open HT
	(
		const wchar_t* fileName //file name
	); //!=Null success complete

	BOOL snap //run snapchot
	(
		HtHandle* htHandle	//manage HT (file and fileMapping)
	);

	BOOL close //snap then close HT and clear htHandle
	(
		const HtHandle* htHandle //manage HT (file and FileMapping)
	); //== true if success complete

	BOOL insert //add element in storage
	(
		HtHandle* htHandle, //manage HT
		const Element* element //element
	); //== true if success complete

	BOOL remove //remove element from storage
	(
		HtHandle* htHandle, //manage HT
		const Element* element //element
	); //== true if success complete

	Element* get //get element from storage
	(
		HtHandle* htHandle, //manage HT
		const Element* element //element
	); //!= NULL if success complete

	BOOL update //update element in storage
	(
		HtHandle* htHandle, //manage HT
		const Element* oldElement, //old element (key, key size)
		const void* newPayLoad, //new data
		int newPayLoadSize //new data size
	); //!= NULL if success complete

	const char* getLastError //get last error message
	(
		const HtHandle* htHandle //manage HT
	);

	void print //print element
	(
		const Element* element //element
	);

	int hash //hash function
	(
		const char* key, //key
		int capacity //storage capacity
	);

	int nextHash //next hash function
	(
		int currentHash, //current hash
		const char* key, //key
		int capacity //storage capacity
	);


	int findFreeIndex //find free index in storage
	(
		const HtHandle* htHandle, //manage HT
		const Element* element //element
	);

	BOOL writeToMemory //write element in memory
	(
		const HtHandle* const htHandle, //manage HT
		const Element* const element, //element
		int index //index
	);

	Element* readFromMemory //read element from memory
	(
		const HtHandle* htHandle, //manage HT
		Element* const element, //element
		int index //index
	);

	int findIndex //find index in storage	
	(
		const HtHandle* const htHandle, //manage HT
		const Element* const element //element
	);

	BOOL clearMemoryByIndex //clear memory by index
	(
		const HtHandle* const htHandle, //manage HT
		int index //index
	);

	void CALLBACK snapAsync //async snapchot
	(
		LPVOID prm, 
		DWORD,
		DWORD
	);

	const char* writeLastError //write last error message
	(
		HtHandle* const htHandle, //manage HT
		const char* message //message
	);

	BOOL runSnapchotTimer //run snapchot timer
	(
		HtHandle* const htHandle //manage HT
	);
}