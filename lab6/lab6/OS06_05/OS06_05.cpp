#include <iostream>
#include <Windows.h>
using namespace std;

#define KB (1024)

void sh(HANDLE pheap)
{
    PROCESS_HEAP_ENTRY phe;
    phe.lpData = NULL;
    while (HeapWalk(pheap, &phe))
    {
        cout << "-- heap start adress = " << hex << phe.lpData
            << ", size = " << dec << phe.cbData
            << ((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") // начало непрерывной области
            << ((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") // нераспределенная область
            << ((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") // распределенная область
            << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

int main()
{
    HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4096 * KB, 0);
    cout << "\n------------Before--------------\n";
    sh(heap);

    int* m = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
    cout << "-- array pointer adress = " << hex << m << " \n\n";
    cout << "\n------------After--------------\n";
    sh(heap);

    HeapFree(heap, HEAP_NO_SERIALIZE, m);
    cout << "\n------------HeapFree--------------\n";
    sh(heap);

    HeapDestroy(heap);

    system("pause");
}
