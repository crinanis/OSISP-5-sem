#include <Windows.h>
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	LPCWSTR OS03_02_1_path = L"e:\\1POIT\\3\\ОСиСП\\Лабы\\lab3\\x64\\Debug\\os03_02_1.exe"; // LP - long pointer, C - const, WSTR - wide character string
	LPCWSTR OS03_02_2_path = L"e:\\1POIT\\3\\ОСиСП\\Лабы\\lab3\\x64\\Debug\\os03_02_2.exe";
	STARTUPINFO si; //Структура STARTUPINFO используется функцией CreateProcess для того, чтобы определить вид основного окна для нового процесса.
	PROCESS_INFORMATION pi1; //Структура PROCESS_INFORMATION заполняется функцией CreateProcess с информацией о недавно созданном процессе и его первичном потоке.
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO)); // предназначена для обнуления памяти, первый аргумент - указатель на начало адреса блока памяти, второй - размер блока памяти в байтах
	si.cb = sizeof(STARTUPINFO); // размер структуры в байтах

	if (CreateProcess(OS03_02_1_path //имя исполняемого модуля
		, NULL //командная строка
		, NULL //(дескриптор безопасности)
		, NULL //(дескриптор безопасности)
		, FALSE //дескриптор параметра наследования
		, CREATE_NEW_CONSOLE // флажки создания
		, NULL // новый блок конфигурации
		, NULL // имя текущего каталога
		, &si // информация предустановки
		, &pi1 // информация о процессе
	))
	{
		std::cout << "Дочерний процесс os03_02_1 создан \n";
	}
	else std::cout << "Дочерний процесс os03_02_1 не создан \n";

	if (CreateProcess(OS03_02_2_path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
	{
		std::cout << "Дочерний процесс os03_02_2 создан \n";
	}
	else std::cout << "Дочерний процесс os03_02_2 не создан \n";


	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 1000; i++)
	{

		Sleep(1000);
		std::cout << "0S03_02: " << pid << " - " << i << "\n";
	}

	WaitForSingleObject(pi1.hProcess, INFINITE); //дождаться завершения процесса, прежде чем продолжить выполнение других действий
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi1.hProcess); //аннулирует заданный дескриптор объекта
	CloseHandle(pi2.hProcess);

	return 0;
}