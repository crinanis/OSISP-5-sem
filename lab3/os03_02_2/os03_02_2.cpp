#include <Windows.h>
#include <iostream>

void main()
{
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 125; i++)
	{
		Sleep(1000);
		std::cout << "0S03_02_2: " << pid << " - " << i << "\n";
	}
}
