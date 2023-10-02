
#include <iostream>
#include <Windows.h>



DWORD WINAPI OS04_02_T1()
{
	for (int i = 0; i < 50; i++)
	{
		std::cout << "\nOS04_02_T1 PID: " << GetCurrentProcessId() << "\tThread Id: " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI OS04_02_T2()
{
	for (int i = 0; i < 125; i++)
	{
		std::cout << "\nOS04_02_T2 PID: " << GetCurrentProcessId() << "\tThread Id: " << GetCurrentThreadId() << "\n";
		Sleep(1000);
	}

	return 0;
}

int main()
{


	HANDLE thread1 = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(OS04_02_T1), NULL, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(OS04_02_T2), NULL, 0, NULL);

	for (int i = 0; i < 100; i++)
	{
		std::cout << "\nMain PID: " << GetCurrentProcessId() << "\n\n";
		Sleep(1000);
	}

	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);





	CloseHandle(thread1);
	CloseHandle(thread2);
}
