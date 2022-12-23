#include <Windows.h>
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

void CreateProccersWithPriority(LPCWSTR an, STARTUPINFO si, int priority)
{
    PROCESS_INFORMATION pi;
    if (priority == 1)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | BELOW_NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 2)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 3)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
    if (priority == 4)
    {
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | REALTIME_PRIORITY_CLASS, NULL, NULL, &si, &pi))
            cout << "-- Process OS05_021 created\n";
        else  cout << "-- Process OS05_021 not created\n";
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    for (int i = 0; i < argc; i++)
    {
        cout << "arg" << i << ": " << argv[i] << endl;
    }

    HANDLE hp = GetCurrentProcess();

    try
    {
        DWORD pa = NULL, sa = NULL, icpu = -1;

        if (!GetProcessAffinityMask(hp, &pa, &sa))
            throw "GetProcessAffinityMask";

        cout << " Process Affinity Mask: " << showbase << hex << pa << "\n";
        cout << " System Affinity Mask: " << showbase << hex << sa << "\n";
        cout << dec << noshowbase << "\n\n";


        if (argv[1] != NULL)
        {
            unsigned long long mask;

            sscanf_s(argv[1], "%d", &mask);

            if (!SetProcessAffinityMask(hp, mask))
                throw "SetProcessAffinityMask";

            if (!GetProcessAffinityMask(hp, &pa, &sa))
                throw "GetProcessAffinityMask";

            cout << " Process Affinity Mask: " << showbase << hex << pa << "\n";
            cout << " System Affinity Mask: " << showbase << hex << sa << "\n";
            cout << dec << noshowbase;

            if (argv[2] != NULL && argv[3] != NULL)
            {
                STARTUPINFO si;

                ZeroMemory(&si, sizeof(STARTUPINFO));
                si.cb = sizeof(STARTUPINFO);

                unsigned long long priority;
                sscanf_s(argv[2], "%d", &priority);

                CreateProccersWithPriority(L"d:\\1POIT\\3\\ОСиСП\\Лабы\\lab5\\Debug\\OS05_02x.exe", si, priority);

                sscanf_s(argv[3], "%d", &priority);

                ZeroMemory(&si, sizeof(STARTUPINFO));
                si.cb = sizeof(STARTUPINFO);

                CreateProccersWithPriority(L"d:\\1POIT\\3\\ОСиСП\\Лабы\\lab5\\Debug\\OS05_02x.exe", si, priority);
            }
        }
    }
    catch (char* msg)
    {
        cout << "Error " << msg << "\n";
    }
}
