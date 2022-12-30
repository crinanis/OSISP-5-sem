#include <iostream>
#include <Windows.h>

using namespace std;
#define PG (4096)
int pg = 256;

int main()
{
    setlocale(LC_ALL, "rus");

    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    int* virtArray = (int*)VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE);
    for (int i = 0; i < pg * PG / 4; i++)
    {
        virtArray[i] = i;
    }

    int char1 = 0xc1;
    int char2 = 0xf3;;
    int char3 = 0xe4;


    int index = (char1 * system_info.dwPageSize + ((char2 << 4) | (char3 >> 4))) / sizeof(int);
    cout << virtArray[index] << endl;

    cout << endl;

    VirtualFree(virtArray, NULL, MEM_RELEASE) ?
        cout << "VirtualFree true\n" : cout << "VirtualFree false\n";
}

    // Б = c1
    // у = f3
    // д = e4


    // c1 = 193 - страница
    // смещение f3e = 3902
    // адрес = PGSIZE * 193 + 3902 = 4096 * 193 + 3902 = 794430 = C1F3E
    // 794430/4 = 198607.5 | 307CF | 0x03 07 CF
