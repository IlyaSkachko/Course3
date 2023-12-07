#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>


int main() {

    setlocale(LC_ALL, "RUS");

    const int PageSize = 4096; 
    const int TotalPages = 256; 

    int totalMemory = PageSize * TotalPages;
    const int elementCount = totalMemory / sizeof(int);
    int* arr = new int[elementCount];

    for (int i = 0; i < elementCount; i++) 
    {
        arr[i] = i;
        //std::cout << arr[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << totalMemory << " байт оперативной памяти." << std::endl;
    std::cout << "Размер страницы памяти: " << PageSize << " байт." << std::endl;
    std::cout << "Общее количество страниц: " << TotalPages << std::endl;
    std::cout << "Количество элементов в массиве: " << elementCount << std::endl;



    unsigned char surname[] = { 0xD1, 0xEA, 0xE0 };

    memcpy(arr, surname, sizeof(surname));

    std::cout << "END";
    return 0;
}


// С - 209(10) - 0xD1(16)
// к - 234(10) - 0xEA(16)
// а - 224(10) - 0xE0(16)

// Страница D1 = 209


// 209 * 4096 = 856064(10) = 0xD1000 - добавить для перехода на страницу
// Смещение EAE = 3758(10) = 0x00000EAE
// Искомое значение: начало массива + 0xD1000 + 0x00000EAE