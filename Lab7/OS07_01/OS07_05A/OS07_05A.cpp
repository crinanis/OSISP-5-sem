#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    int start = clock();

    DWORD pid = GetCurrentProcessId();
    HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event");

    he == NULL ? cout << "OS07_05A: Open Error Event\n" : cout << "OS07_05A: Open Event\n";

    WaitForSingleObject(he, INFINITE);
    for (int i = 0; i < 90; i++) {
        cout << i << " OS07_05A pid = " << pid << ", time: " << clock() - start << endl;
        Sleep(100);
    }

    CloseHandle(he);

    system("pause");
    return 0;
}