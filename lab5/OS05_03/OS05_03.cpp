#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <time.h>

using namespace std;

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);

    switch (prty)
    {
    case IDLE_PRIORITY_CLASS:
        cout << " IDLE_PRIORITY_CLASS";
        break;
    case BELOW_NORMAL_PRIORITY_CLASS:
        cout << "BELOW_NORMAL_PRIORITY_CLASS";
        break;
    case NORMAL_PRIORITY_CLASS:
        cout << "NORMAL_PRIORITY_CLASS";
        break;
    case ABOVE_NORMAL_PRIORITY_CLASS:
        cout << "ABOVE_NORMAL_PRIORITY_CLASS";
        break;
    case HIGH_PRIORITY_CLASS:
        cout << "HIGH_PRIORITY_CLASS";
        break;
    case REALTIME_PRIORITY_CLASS:
        cout << "REALTIME_PRIORITY_CLASS";
        break;
    default:
        cout << "?";
        break;
    }
    return;
}

void printThreadPrty(HANDLE h)
{
    DWORD prty = GetThreadPriority(h);

    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST:
        cout << "THREAD_PRIORITY_LOWEST";
        break;
    case THREAD_PRIORITY_BELOW_NORMAL:
        cout << "THREAD_PRIORITY_BELOW_NORMAL";
        break;
    case THREAD_PRIORITY_NORMAL:
        cout << "THREAD_PRIORITY_NORMAL";
        break;
    case THREAD_PRIORITY_ABOVE_NORMAL:
        cout << "THREAD_PRIORITY_ABOVE_NORMAL";
        break;
    case THREAD_PRIORITY_HIGHEST:
        cout << "THREAD_PRIORITY_HIGHEST";
        break;
    case THREAD_PRIORITY_IDLE:
        cout << "THREAD_PRIORITY_IDLE";
        break;
    case THREAD_PRIORITY_TIME_CRITICAL:
        cout << "THREAD_PRIORITY_TIME_CRITICAL";
        break;
    default:
        cout << "?"; break;
    }
    return;
}

void SetProccesPriority(HANDLE hp, int priority)
{
    if (priority == 1)
    {
        SetPriorityClass(hp, IDLE_PRIORITY_CLASS);
    }
    if (priority == 2)
    {
        SetPriorityClass(hp, NORMAL_PRIORITY_CLASS);
    }
    if (priority == 3)
    {
        SetPriorityClass(hp, HIGH_PRIORITY_CLASS);
    }
    if (priority == 4)
    {
        SetPriorityClass(hp, REALTIME_PRIORITY_CLASS);
    }
}

DWORD WINAPI TA()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);

    cout << endl << endl;
    double t1, t2;

    t1 = clock();
    for (unsigned long i = 1; i <= 100000000; i++)
    {
        if (i % 1000 == 0)
        {
            Sleep(200);

            cout << i << ": PID = " << GetCurrentProcessId() << "; TID = " << GetCurrentThreadId() << "; Pprty class = ";
            printProcessPrty(hp);
            cout << "; Tprty = ";
            printThreadPrty(ht);
            cout << "; Current processor = " << icpu << endl;
        }
    }
    t2 = clock();

    cout << "\nTID: " << GetCurrentThreadId() << "has finished. Time:" << t2 - t1 << "ms." << endl << endl;

    return 0;
}

void SetPriorityThread(HANDLE hp, int priority)
{
    switch (priority)
    {
    case 1:
        SetThreadPriority(hp, THREAD_PRIORITY_IDLE);
        break;
    case 2:
        SetPriorityClass(hp, THREAD_PRIORITY_LOWEST);
        break;
    case 3:
        SetPriorityClass(hp, THREAD_PRIORITY_BELOW_NORMAL);
        break;
    case 4:
        SetPriorityClass(hp, THREAD_PRIORITY_NORMAL);
        break;
    case 5:
        SetPriorityClass(hp, THREAD_PRIORITY_ABOVE_NORMAL);
        break;
    case 6:
        SetThreadPriority(hp, THREAD_PRIORITY_HIGHEST);
        break;
    case 7:
        SetThreadPriority(hp, THREAD_PRIORITY_TIME_CRITICAL);
        break;
    default:
        SetPriorityClass(hp, THREAD_PRIORITY_NORMAL);
        break;
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    for (int i = 0; i < argc; i++)
    {
        cout << "arg" << i << ": " << argv[i] << "\n";
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


            if (argv[2] != NULL && argv[3] != NULL && argv[4] != NULL)
            {
                int priority = 0;
                sscanf_s(argv[2], "%d", &priority);
                SetProccesPriority(GetCurrentProcess(), priority);

                sscanf_s(argv[3], "%d", &priority);

                DWORD ChildId1 = NULL;
                HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId1);
                SetPriorityThread(hChild1, priority);
                ResumeThread(hChild1);

                sscanf_s(argv[4], "%d", &priority);

                DWORD ChildId2 = NULL;
                HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId2);
                SetPriorityThread(hChild2, priority);
                ResumeThread(hChild2);
            }
        }
    }
    catch (char* msg)
    {
        cout << "Error " << msg << "\n";
    }


    system("pause");
}
