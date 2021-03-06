//The following example creates a timer that will be signaled after a 10 second delay. 
//First, the code uses the CreateWaitableTimer function to create a waitable timer object. 
//Then it uses the SetWaitableTimer function to set the timer. 
//The code uses the WaitForSingleObject function to determine when the timer has been signaled. 


/* without the next line the code will not compile */
#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <stdio.h>



int main()
{
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;

    liDueTime.QuadPart=-100000000;

    // Create a waitable timer.
    hTimer = CreateWaitableTimer(NULL, TRUE, "WaitableTimer");
    if (!hTimer)
    {
        printf("CreateWaitableTimer failed (%d)\n", GetLastError());
        return 1;
    }

    printf("Waiting for 10 seconds...\n");

    // Set a timer to wait for 10 seconds.
    if (!SetWaitableTimer(
        hTimer, &liDueTime, 0, NULL, NULL, 0))
    {
        printf("SetWaitableTimer failed (%d)\n", GetLastError());
        return 2;
    }

    // Wait for the timer.

    if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
        printf("WaitForSingleObject failed (%d)\n", GetLastError());
    else printf("Timer was signaled.\n");

    return 0;
}
