#include <iostream>
#include <ctime>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#define UNICODE 1
#define _UNICODE 1

#define SECOND 10000000
clock_t start;
int iteration;
bool finish = false;
using namespace std;

VOID CALLBACK TimerAPCProc(LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
    // Formal parameters not used in this example.
    UNREFERENCED_PARAMETER(dwTimerLowValue);
    UNREFERENCED_PARAMETER(dwTimerHighValue);

    cout << "i - " << iteration << ", mc - " << clock() - start << endl;
    if ((clock() - start) / CLOCKS_PER_SEC >= 15)
    {
        finish = true;
    }
    MessageBeep(0);

}

int main(void)
{
    HANDLE          hTimer;
    BOOL            bSuccess;
    __int64         qwDueTime;
    LARGE_INTEGER   liDueTime;

    hTimer = CreateWaitableTimer(NULL, FALSE, TEXT("MyTimer"));
    if (hTimer != NULL)
    {
        __try
        {
            qwDueTime = -3 * SECOND;

            liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
            liDueTime.HighPart = (LONG)(qwDueTime >> 32);

            bSuccess = SetWaitableTimer(hTimer, &liDueTime, 3000, TimerAPCProc, NULL, FALSE);
            start = clock();
            if (bSuccess)
            {
                for (iteration = 0;; iteration++)
                {
                    SleepEx(0, TRUE);
                    if (finish)
                    {
                        break;
                    }
                }
            }
            else
            {
                printf("SetWaitableTimer failed with error %d\n", GetLastError());
            }

        }
        __finally
        {
            CloseHandle(hTimer);
        }
    }
    else
    {
        printf("CreateWaitableTimer failed with error %d\n", GetLastError());
    }

    return 0;
}