#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    int start = clock();

    DWORD pid = GetCurrentProcessId();
    HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");

    hm == NULL ? cout << "OS07_03B: Open Error Mutex\n" : cout << "OS07_03B: Open Mutex\n";

    for (int i = 0; i < 90; i++) {
        if (i == 30) {
            WaitForSingleObject(hm, INFINITE);
        }
        if (i == 60) {
            ReleaseMutex(hm);
        }

        cout << i << " OS07_03B pid = " << pid << ", time: " << clock() - start << endl;
        Sleep(100);
    }

    CloseHandle(hm);

    system("pause");
    return 0;
}