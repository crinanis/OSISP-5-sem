#include <Windows.h>
#include <iostream>

using namespace std;

void main()
{
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 100000; i++)
	{
		cout << pid << " - " << i << endl;
		Sleep(1000);
	}
}