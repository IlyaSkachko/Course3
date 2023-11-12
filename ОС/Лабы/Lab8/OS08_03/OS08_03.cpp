#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>


std::string convert(wchar_t letter)
{
    std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> wideConv(new std::codecvt_byname<wchar_t, char, std::mbstate_t>("ru_RU.CP1251"));

    std::string hexValue = wideConv.to_bytes(letter);
    std::cout << "Шестнадцатеричное представление буквы: ";
    for (char c : hexValue) {
        std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(c));
    }
    std::cout << std::endl;

    return hexValue;
}


int main() {

    setlocale(LC_ALL, "RUS");

    const int PageSize = 4096; 
    const int TotalPages = 256; 

    int totalMemory = PageSize * TotalPages;
    const int elementCount = totalMemory / sizeof(int);
    std::vector<int> arr(elementCount);

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


    wchar_t letters[3] = {L'С', L'к', L'а'};

    for (auto l : letters)
    {
        convert(l);
    }


    // Записываем 3 первые буквы фамилии в кодировке Windows-1251
    unsigned char surname[] = { 0xD1, 0xEA, 0xE0 };

    // Вычисляем адрес на основе указанного принципа
    unsigned char pageNumber = surname[0];
    unsigned short offset = (surname[1] << 8) | surname[2];

    unsigned char* address = reinterpret_cast<unsigned char*>(pageNumber * 256 + offset);

    std::cout << "Адрес: " << static_cast<void*>(address) << std::endl;
    std::cout << "Значение в байте по адресу: " << static_cast<int>(*address) << std::endl;


    return 0;
}