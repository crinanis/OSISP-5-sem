#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;
DWORD WINAPI A();
DWORD WINAPI B();

CRITICAL_SECTION cs;

int main() {
	pid = GetCurrentProcessId();

	InitializeCriticalSection(&cs);

	DWORD tid = GetCurrentThreadId();
	DWORD AId = NULL, BId = NULL;
	HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)A, NULL, 0, &AId);
	HANDLE hB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)B, NULL, 0, &BId);

	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		cout << i << " pid = " << pid << ", main tid = " << tid << ", time: " << clock() - start << endl;
		Sleep(100);
	}

	WaitForSingleObject(hA, INFINITY);	WaitForSingleObject(hB, INFINITY);
	DeleteCriticalSection(&cs);

	CloseHandle(hA); CloseHandle(hB);

	system("pause");
	return 0;
}

DWORD WINAPI A() {
	DWORD tid = GetCurrentThreadId();

	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		cout << i << " pid = " << pid << ", A tid = " << tid << ", time: " << clock() - start << endl;
		Sleep(100);
	}

	return 0;
}

DWORD WINAPI B() {
	DWORD tid = GetCurrentThreadId();

	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		cout << i << " pid = " << pid << ", B tid = " << tid << ", time: " << clock() - start << endl;
		Sleep(100);
	}

	return 0;
}