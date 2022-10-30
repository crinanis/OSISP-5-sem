#include <Windows.h>
#include <iostream>
#include "windows.h"
#include "tlhelp32.h"
#include <iomanip>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0); 
	// HANDLE - дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс.
	// получение снимка (snapshot) системы, который содержит информацию о состоянии системы в момент выполнения снимка.
	// Снимок создается с помощью функции CreateToolHelp32Snapshot(dwFlags, th32ProcessID), первый аргумент определяет, какая информация будет записана в снимок.
	// TH32CS_SnapALL - В снимок включается список куч, процессов, потоков и модулей
	// Второй аргумент определяет процесс, информация о котором необходима (если требуется список куч и модулей). В остальных случаях он игнорируется. 
	// снепшот — моментальный снимок, копия файлов и каталогов файловой системы на определённый момент времени.
	PROCESSENTRY32 peProcessEntry; // Описывает структуру списка процессов, находящихся в адресном пространстве системы в момент снимка.
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	wcout << L"Current PID = " << pid << endl << L"-----------------------------------" << endl;
	try
	{
		if (!Process32First(snap, &peProcessEntry)) //Извлекает информацию о первом процессе снимка, полученного посредством CreateToolhelp32Snapshot
			throw L"Process32First";
		do
		{
			wcout << L"Name\t\t" << peProcessEntry.szExeFile << endl //Десятое поле – szExeFile – содержит имя файла, создавшего процесс.
				<< L"PID\t\t" << peProcessEntry.th32ProcessID;
			if (peProcessEntry.th32ProcessID == pid)
				wcout << " --> current process";
			wcout << L"\nParent ID\t" << peProcessEntry.th32ParentProcessID;

			wcout << endl << L"-----------------------------------" << endl;

		} while (Process32Next(snap, &peProcessEntry)); //Соответственно извлекает информацию о следующем процессе
	}
	catch (char* msg)
	{
		wcout << L"ERROR: " << msg << endl;
	}

	system("pause");
	return 0;
}


