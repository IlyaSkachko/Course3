

#include <iostream>
#include <Windows.h>


void sh(HANDLE heap)
{
    PROCESS_HEAP_ENTRY entry = {};

    size_t totalSize = 0;
    SIZE_T usedSize = 0;
    SIZE_T freeSize = 0;

    while (HeapWalk(heap, &entry)) {
        totalSize += entry.cbData;

        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
            usedSize += entry.cbData;
        else
            freeSize += entry.cbData;
    }

    std::cout << "\n\nОбщий размер heap: " << totalSize << " байт" << std::endl;
    std::cout << "Размер распределенной памяти: " << usedSize << " байт" << std::endl;
    std::cout << "Размер нераспределенной памяти: " << freeSize << " байт" << std::endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4000000, 100000000);

    std::cout << "\n\n---------- Create ----------------" << std::endl;

    sh(heap);

    int* arr = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 3000 * sizeof(int));        

    std::cout << "\n\n---------- Add Array ----------------" << std::endl;
    sh(heap);


    HeapFree(heap, HEAP_NO_SERIALIZE, arr);

    std::cout << "\n\n---------- Heap Free ----------------" << std::endl;
    sh(heap);


    HeapDestroy(heap);
    std::cout << "\n\n---------- Destroy Heap ----------------" << std::endl;


    system("pause");
    return 0;
}

