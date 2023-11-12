

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

    HANDLE heap = GetProcessHeap();

    sh(heap);

    int* arr = new int[300000];

    sh(heap);

    return 0;
}

