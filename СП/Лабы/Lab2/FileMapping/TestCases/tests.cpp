#include "tests.h"

namespace tests
{
	BOOL test1(HT::HtHandle* ht)
	{

		if (!HT::insert(ht, new HT::Element("newKey", 7, "data", 5)))
		{
			if (strcmp("error: so long key", HT::getLastError(ht)) == 0)
			{
				return true;
			}
		}
		return false;
	}

	BOOL test2(HT::HtHandle* ht)
	{

		if (!HT::insert(ht, new HT::Element("newKe", 7, "dataFile", 9)))
		{
			if (strcmp("error: so long payload", HT::getLastError(ht)) == 0)
			{
				return true;
			}
		}
		return false;

	}

	BOOL test3(HT::HtHandle* ht)
	{
		HT::Element* element = new HT::Element("test22", 7, "dataInfo", 9);
		if (HT::get(ht, element) == NULL)
		{
			if (strcmp("error: file not found", HT::getLastError(ht)) == 0)
			{
				return true;
			}
		}
		return false;
	}

	BOOL test4(HT::HtHandle* ht)
	{

		HT::Element* element = new HT::Element("test2", 6, "dataInfo", 9);
		HT::remove(ht, element);
		if (!HT::remove(ht, element))
		{
			if (strcmp("error: element is already remove", HT::getLastError(ht)) == 0)
			{
				return true;
			}
		}
		return false;
	}

	BOOL test5(HT::HtHandle* ht)
	{
		HT::Element* element = new HT::Element("test2", 6, "test2", 6);

		HT::insert(ht, element);
		HT::remove(ht, element);
		if (HT::get(ht, element) != NULL)
			return false;

		return true;
	}
}