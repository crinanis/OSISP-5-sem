//1. Напишите ассемблерный  код с применением команд BTS или BTR, 
//демонстрирующий реализацию  механизма синхронизации двух потоков одного процесса и поясните  его работу.

#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

DWORD WINAPI A();
DWORD WINAPI B();

void EnterCriticalSectionAssem();
void LeaveCriticalSectionAssem();

int check = 0;

int main() {
	DWORD AId = NULL, BId = NULL;
	HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)A, NULL, 0, &AId);
	HANDLE hB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)B, NULL, 0, &BId);

	WaitForSingleObject(hA, INFINITY);	WaitForSingleObject(hB, INFINITY);
	CloseHandle(hA); CloseHandle(hB);

	system("pause");
	return 0;
}

DWORD WINAPI A() {
	int start = clock();

	EnterCriticalSectionAssem();
	for (int i = 0; i < 5; i++) {
		cout << "A:" << i << ", time: " << clock() - start << endl;
	}
	LeaveCriticalSectionAssem();

	return 0;
}

DWORD WINAPI B() {
	int start = clock();

	EnterCriticalSectionAssem();
	for (int i = 0; i < 5; i++) {
		cout << "B:" << i << ", time: " << clock() - start << endl;
	}
	LeaveCriticalSectionAssem();

	return 0;
}

void EnterCriticalSectionAssem() {
	_asm {
	CriticalSection:
		lock bts check, 0;
		jc CriticalSection
	}
}

void LeaveCriticalSectionAssem() {
	_asm lock btr check, 0
}