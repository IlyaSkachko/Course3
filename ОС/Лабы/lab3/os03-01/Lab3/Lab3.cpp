#include <iostream>
#include <windows.h>
 
int main()
{
    for (int i = 0; i < 10000; ++i) {

        Sleep(1000);
        std::cout << GetCurrentProcessId() << " - " << i + 1 << std::endl;
    }

    return 0;
}