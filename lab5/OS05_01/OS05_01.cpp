#include <Windows.h>
#include <iostream>
#include <bitset>

using namespace std;

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);
    cout << " ----- Current PID = " << GetCurrentProcessId() << " \n";
    switch (prty)
    {
    case IDLE_PRIORITY_CLASS:
        cout << " ----+ priority = IDLE_PRIORITY_CLASS \n";
        break;
    case BELOW_NORMAL_PRIORITY_CLASS:
        cout << " ----+ priority = BELOW_NORMAL_PRIORITY_CLASS \n";
        break;
    case NORMAL_PRIORITY_CLASS:
        cout << " ----+ priority = NORMAL_PRIORITY_CLASS \n";
        break;
    case ABOVE_NORMAL_PRIORITY_CLASS:
        cout << " ----+ priority = ABOVE_NORMAL_PRIORITY_CLASS \n";
        break;
    case HIGH_PRIORITY_CLASS:
        cout << " ----+ priority = HIGH_PRIORITY_CLASS \n";
        break;
    case REALTIME_PRIORITY_CLASS:
        cout << " ----+ priority = REALTIME_PRIORITY_CLASS \n";
        break;
    default:
        cout << " ----+ priority = ? \n";
        break;
    }
    return;
}

void printThreadPrty(HANDLE h)
{
    DWORD icpu = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);
    DWORD prty = GetThreadPriority(h);
    cout << " ---- Current Thread ID = " << GetCurrentThreadId() << "\n";
    cout << " ----+ Processor = " << icpu << " \n";
    //cout << " ----+ MAXProcessors = " << MAXIMUM_PROCESSORS << " \n";

   

    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST:
        cout << " ----+ priority = THREAD_PRIORITY_LOWEST \n";
        break;
    case THREAD_PRIORITY_BELOW_NORMAL:
        cout << " ----+ priority = THREAD_PRIORITY_BELOW_NORMAL \n";
        break;
    case THREAD_PRIORITY_NORMAL:
        cout << " ----+ priority = THREAD_PRIORITY_NORMAL \n";
        break;
    case THREAD_PRIORITY_ABOVE_NORMAL:
        cout << " ----+ priority = THREAD_PRIORITY_ABOVE_NORMAL \n";
        break;
    case THREAD_PRIORITY_HIGHEST:
        cout << " ----+ priority = THREAD_PRIORITY_HIGHEST \n";
        break;
    case THREAD_PRIORITY_IDLE:
        cout << " ----+ priority = THREAD_PRIORITY_IDLE \n";
        break;
    case THREAD_PRIORITY_TIME_CRITICAL:
        cout << " ----+ priority = THREAD_PRIORITY_TIME_CRITICAL \n";
        break;
    default:
        cout << " ----+ priority = ? \n"; break;
    }
    return;
}

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    cout << " =====================OS05_01=======================\n";
    try
    {
        {
            DWORD pa = NULL, sa = NULL, icpu = -1;
            if (!GetProcessAffinityMask(hp, &pa, &sa))
                throw "GetProcessAffinityMask";

            bitset<8> pa_bits(pa); //числа в двоичном формате (например, bin). Если необходим двоичный вывод 
            //можно использовать трюк std::bitset:
            cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
            //showbase - Выводить индикатор основания   системы счисления
            cout << " Process Affinity Mask: " << pa_bits << "\n";
            bitset<8> sa_bits(sa);

            cout << " System Affinity Mask: " << std::showbase << sa << "\n";
            cout << " System Affinity Mask: " << sa_bits << "\n";
            cout << " Processors: " << std::noshowbase << sa_bits.count() << "\n";
        }
    }
    catch (char* msg)
    {
        cout << "Error " << msg << endl;
    }
    cout << dec << noshowbase;

    printProcessPrty(hp);
    printThreadPrty(ht);
    cout << "\n\n";

    cout << " =====================================================\n";
    system("pause");
    return 0;
}