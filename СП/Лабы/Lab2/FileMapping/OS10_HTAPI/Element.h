#pragma once

namespace HT
{
	struct Element
	{
		Element();
		Element(const void* key, int keyLength);                                             // for get
		Element(const void* key, int keyLength, const void* payload, int  payloadLength);    // for insert
		Element(const Element* oldElement, const void* newPayload, int  newPayloadLength);   // for update
		const void* key;                 // key value
		int         keyLength;           // key size
		const void* payload;             // данные 
		int         payloadLength;       // размер данных
	};

	int getSizeElement(
		int maxKeyLength,
		int maxPayloadLength
	);
};