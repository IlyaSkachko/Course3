// OS03_02_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

int main()
{
    for (int i = 0; i < 50; ++i)
    {
        std::cout << std::endl << std::endl << std::endl;
        std::cout << std::endl  <<   GetCurrentProcessId() << " - " << i + 1 << std::endl << std::endl;
        Sleep(1000);
    }
}
