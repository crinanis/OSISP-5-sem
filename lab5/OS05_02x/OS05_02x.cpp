#include <Windows.h>
#include <iostream>
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

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);

    double t1, t2;

    t1 = clock();
    for (unsigned long i = 1; i <= 1000000; i++)
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

    cout << "\ntime:" << t2 - t1 << "ms." << endl << endl;

    system("pause");
}


