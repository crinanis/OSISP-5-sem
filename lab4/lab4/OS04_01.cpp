#include <Windows.h>
#include <iostream>

void main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 100000; i++)
	{
		std::cout << "----------------------" << std::endl;
		std::cout << "pid: " << pid << std::endl;
		std::cout << "tid: " << tid << std::endl;
		std::cout << "----------------------" << std::endl;
		Sleep(1000);
	}
}