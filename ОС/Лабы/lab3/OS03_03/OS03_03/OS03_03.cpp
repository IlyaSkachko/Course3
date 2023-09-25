
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

void ListProcesses()
{
    // Создаем снимок текущего состояния процессов
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create a process snapshot." << std::endl;
        return;
    }

    // Инициализируем структуру для получения информации о процессе
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Получаем информацию о первом процессе в снимке
    if (!Process32First(hSnapshot, &pe32))
    {
        std::cerr << "Failed to retrieve information about the first process." << std::endl;
        CloseHandle(hSnapshot);
        return;
    }

    // Выводим информацию о каждом процессе
    do
    {
        std::cout << "Process ID: " << pe32.th32ProcessID << std::endl;
        std::wcout << L"Process Name: " << pe32.szExeFile << std::endl;
        std::cout << std::endl;
    } while (Process32Next(hSnapshot, &pe32));

    // Закрываем дескриптор снимка
    CloseHandle(hSnapshot);
}

int main()
{
    ListProcesses();

    return 0;
}