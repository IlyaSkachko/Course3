#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>


DWORD WINAPI OS04_03_T1()
{
    for (int i = 0; i < 50; i++)
    {
        std::cout << "\nOS04_02_T1 PID: " << GetCurrentProcessId() << "\tThread Id: " << GetCurrentThreadId() << "\n";
        Sleep(1000);
    }

    return 0;
}

DWORD WINAPI OS04_03_T2()
{
    for (int i = 0; i < 125; i++)
    {
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

  
        if (i == 5) {
            SuspendThread(thread1.native_handle()); 
        }

  
        if (i == 8) {
            SuspendThread(thread2.native_handle());
        }

        if (i == 12) {
            ResumeThread(thread1.native_handle());
        }


        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    thread1.join();
    thread2.join();

    return 0;
}