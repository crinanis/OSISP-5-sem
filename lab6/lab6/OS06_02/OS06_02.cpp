#include <iostream>
#include <Windows.h>

int main()
{
    for (int i = 0; i < 1000000; i++)
    {
        std::cout << "iterator: " << i << std::endl;
        Sleep(1000);
    }
}