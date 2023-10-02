#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>


DWORD WINAPI OS04_03_T1()
{
    for (int i = 0; i < 50; i++)
    {
        if (i == 25)
        {
            Sleep(10000);
        }

        std::cout << "\nOS04_02_T1 PID: " << GetCurrentProcessId() << "\tThread Id: " << GetCurrentThreadId() << "\n";
        Sleep(1000);
    }

    return 0;
}

DWORD WINAPI OS04_03_T2()
{
    for (int i = 0; i < 125; i++)
    {
        if (i == 80)
        {
            Sleep(15000);
        }

        std::cout << "\nOS04_02_T2 PID: " << GetCurrentProcessId() << "\tThread Id: " << GetCurrentThreadId() << "\n";
        Sleep(1000);
    }

    return 0;
}

int main() {

    std::thread thread1(OS04_03_T1);
    std::thread thread2(OS04_03_T2);

    for (int i = 0; i < 100; i++) {

        DWORD processId = GetCurrentProcessId();


        std::cout << "\n" << i << ". Main PID: " << processId << std::endl;


        
        if (i == 30)
        {
            Sleep(10000);
        }

        Sleep(1000);
    }

    thread1.join();
    thread2.join();

    return 0;
}