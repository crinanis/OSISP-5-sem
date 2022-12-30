#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    int start = clock();

    DWORD pid = GetCurrentProcessId();
    HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Semaphore");

    hs == NULL ? cout << "OS07_04B: Open Error Semaphore\n" : cout << "OS07_04B: Open Semaphore\n";

    for (int i = 0; i < 90; i++) {
        if (i == 30) {
            WaitForSingleObject(hs, INFINITE);
        }
        if (i == 60) {
            ReleaseSemaphore(hs, 1, 0);
        }

        cout << i << " OS07_04B pid = " << pid << ", time: " << clock() - start << endl;
        Sleep(100);
    }

    CloseHandle(hs);

    system("pause");
    return 0;
}