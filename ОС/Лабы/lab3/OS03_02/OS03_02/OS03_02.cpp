#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

int main()
{
    // Создание первого дочернего процесса
    STARTUPINFO si1 = { sizeof(si1) };
    PROCESS_INFORMATION pi1;
    std::wstring commandLine1 = L"OS03_02_1.exe";

    if (CreateProcess(NULL, &commandLine1[0], NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1))
    {
        // Создание второго дочернего процесса
        STARTUPINFO si2 = { sizeof(si2) };
        PROCESS_INFORMATION pi2;
        std::wstring commandLine2 = L"OS03_02_2.exe";
        if (CreateProcess(NULL, &commandLine2[0], NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
        {
            // Ожидание завершения обоих дочерних процессов
            WaitForSingleObject(pi1.hProcess, INFINITE);
            WaitForSingleObject(pi2.hProcess, INFINITE);
            

            // Закрытие дескрипторов процессов
            CloseHandle(pi1.hProcess);
            CloseHandle(pi1.hThread);
            CloseHandle(pi2.hProcess);
            CloseHandle(pi2.hThread);
        }
        else
        {
            std::cerr << "Failed to create OS03_02_2 process." << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << "Failed to create OS03_02_1 process." << std::endl;
        return 1;
    }

    return 0;
}