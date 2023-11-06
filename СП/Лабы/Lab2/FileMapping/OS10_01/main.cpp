#include <iostream>
#include"HT.h"
#include <vector>
using namespace std;

void main()
{
	//------------- CreateFile ------------------
	HT::HtHandle* ht = nullptr;

	try
	{
		ht = HT::create(1000, 3, 10, 256, L"./files/HTFile.ht");
		if (ht)
			cout << "-- create: success" << endl;
		else
			throw "-- create: error";

		if(HT::insert(ht, new HT::Element("key", 4, "payload", 8)))
			cout << "-- insert: success" << endl;
		else
			throw "-- insert: error";

		HT::Element* hte = HT::get(ht, new HT::Element("key", 4));
		if (hte)
		{
			cout << "-- get: success" << endl;
		}
		else
			throw "-- get: error";

		HT::print(hte);

		if (HT::update(ht, hte, "newPayload", 11))
			cout << "-- update: success" << endl;
		else
			throw "-- update: error";

		if (HT::snap(ht))
			cout << "-- snapSync: success" << endl;
		else
			throw "-- snap: error";

		hte = HT::get(ht, new HT::Element("key", 4));
		if (hte)
			cout << "-- get: success" << endl;
		else
			throw "-- get: error";

		HT::print(hte);

		SleepEx(3000, TRUE);

		if (HT::remove(ht, hte))
			cout << "-- remove: success" << endl;
		else
			throw "-- remove: error";

		hte = HT::get(ht, new HT::Element("key", 4));
		if (hte)
			cout << "-- get: success" << endl;
		else
			throw "-- get: error";
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht != nullptr)
			cout << HT::getLastError(ht) << endl;
	}

	//---------------- Close ------------------
	try
	{
		if (ht != nullptr)
			if (HT::close(ht))
				cout << "-- close: success" << endl;
			else
				throw "-- close: error";
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}


	//---------------- Open ------------------
	try
	{
		ht = HT::open(L"./files/HTFile.ht"); 
		if (ht)
			cout << "-- open: success" << endl;
		else
			throw "-- open: error";

		if (HT::insert(ht, new HT::Element("key22", 6, "payload", 8)))
			cout << "-- insert: success" << endl;
		else
			throw "-- insert: error";

		HT::Element* hte = HT::get(ht, new HT::Element("key22", 6));
		if (hte)
		{
			cout << "-- get: success" << endl;
		}
		else
			throw "-- get: error";

		HT::print(hte);


		if (ht != nullptr)
			if (HT::close(ht))
				cout << "-- close: success" << endl;
			else
				throw "-- close: error";
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht != nullptr)
			cout << HT::getLastError(ht) << endl;
	}
}
