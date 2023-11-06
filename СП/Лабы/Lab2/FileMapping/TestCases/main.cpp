#include "tests.h"

using namespace std;

void main()
{
	HT::HtHandle* ht = HT::create(1000, 3, 15, 256, L"./files/HTspace.ht");
	bool resultTest;

	cout << "------------- TEST1 -------------" << endl;
	if (resultTest = tests::test1(ht))
	{
		cout << "test 1 complete!" << endl;
	}
	else
	{
		cout << "test 1 failed!" << endl;
	}

	cout << "------------- TEST2 -------------" << endl;
	if (resultTest = tests::test2(ht))
	{
		cout << "test 2 complete!" << endl;
	}
	else
	{
		cout << "test 2 failed!" << endl;
	}

	cout << "------------- TEST3 -------------" << endl;
	if (resultTest = tests::test3(ht))
	{
		cout << "test 3 complete!" << endl;
	}
	else
	{
		cout << "test 3 failed!" << endl;
	}

	cout << "------------- TEST4 -------------" << endl;
	if (resultTest = tests::test4(ht))
	{
		cout << "test 4 complete!" << endl;
	}
	else
	{
		cout << "test 4 failed!" << endl;
	}

	cout << "------------- TEST5 -------------" << endl;
	if (resultTest = tests::test5(ht))
	{
		cout << "test 5 complete!" << endl;
	}
	else
	{
		cout << "test 5 failed!" << endl;
	}

	if (ht != nullptr)
		if (HT::close(ht))
			cout << "\n-- close: success" << endl;
		else
			throw "-- close: error";
}