#include <Windows.h>
#include <iostream>

static DWORD pid;

DWORD WINAPI OS04_02_T1()
{
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		std::cout << "-----OS_04_02_T1-----" << std::endl;
		std::cout << "pid: " << pid << std::endl;
		std::cout << "tid: " << tid << std::endl;
		std::cout << "---------------------" << std::endl;
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI OS04_02_T2()
{
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		std::cout << "-----OS_04_02_T2-----" << std::endl;
		std::cout << "pid: " << pid << std::endl;
		std::cout << "tid: " << tid << std::endl;
		std::cout << "---------------------" << std::endl;
		Sleep(1000);
	}

	return 0;
}

int main()
{
	pid = GetCurrentProcessId();

	DWORD tid = GetCurrentThreadId();
	DWORD ChildId_T1 = NULL;
	DWORD ChildId_T2 = NULL;

	HANDLE h1Child = CreateThread(NULL, // аттрибут безопасности по умолчанию
									0, // размер стека по умолчанию
									(LPTHREAD_START_ROUTINE)OS04_02_T1, // функция потока, начальный адрес кода, с которого поток начнёт выполняться
									NULL, // аргумент функции потока
									0, // флажки создания по умолчанию
									&ChildId_T1 // возвращает идентификатор потока
								);
	HANDLE h2Child = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_02_T2, NULL, 0, &ChildId_T2);
	for (int i = 0; i < 100; i++)
	{
		std::cout << "--------Parent thread--------" << std::endl;
		std::cout << "pid: " << pid << std::endl;
		std::cout << "parent tid: " << tid << std::endl;
		std::cout << "child tid T1: " << ChildId_T1 << std::endl;
		std::cout << "child tid T2: " << ChildId_T2 << std::endl;
		std::cout << "-----------------------------" << std::endl;
		Sleep(1000);
	}

	WaitForSingleObject(h1Child, INFINITE);
	CloseHandle(h1Child);

	WaitForSingleObject(h2Child, INFINITE);
	CloseHandle(h2Child);

	system("pause");
	return 0;
}