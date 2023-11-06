#ifdef _WIN64
#pragma comment(lib, "../x64/debug/OS10_HTAPI.lib")
#else
#pragma comment(lib, "../debug/OS10_HTAPI.lib")
#endif

#include "../OS10_HTAPI/pch.h"
#include "../OS10_HTAPI/HT.h"
using namespace std;

#pragma warning (disable : 4996)

void main()
{
	HT::HtHandle* ht1 = nullptr;
	HT::HtHandle* ht2 = nullptr;

#pragma region HT1

	try
	{
		cout << "----------- HT1 -----------" << endl;
		ht1 = HT::create(1000, 3, 10, 256, L"./files/HTspace.ht");
		if (ht1)
			cout << "-- create: success" << endl;
		else
			throw "-- create: error";

		cout << "HT1: " << ht1->addr << endl;

		if (HT::insert(ht1, new HT::Element("key", 4, "payload", 8)))
			cout << "-- insert: success" << endl;
		else
			throw "-- insert: error";
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht1 != nullptr)
			cout << HT::getLastError(ht1) << endl;
	}

#pragma endregion

#pragma region HT2

	try
	{
		cout << "\n----------- HT2 -----------" << endl;
		ht2 = HT::open(L"./files/HTspace.ht", true);
		if (ht2)
			cout << "-- open: success" << endl;
		else
			throw "-- open: error";

		cout << "HT2: " << ht2->addr << endl;

		HT::Element* hte = HT::get(ht2, new HT::Element("key", 4));
		if (hte)
			cout << "-- get: success" << endl;
		else
			throw "-- get: error";

		HT::print(hte);
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht2 != nullptr)
			cout << HT::getLastError(ht2) << endl;
	}

#pragma endregion

	try
	{
		if (ht1 != nullptr)
			if (HT::close(ht1))
				cout << "-- close: success (HT1)" << endl;
			else
				throw "-- close: error (HT1)";

		if (ht2 != nullptr)
			if (HT::close(ht2))
				cout << "-- close: success (HT2)" << endl;
			else
				throw "-- close: error (HT2)";
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
