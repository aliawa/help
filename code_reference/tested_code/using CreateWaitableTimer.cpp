/* The next line is critical for compilation */
#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <stdio.h>

VOID CALLBACK TimeUp(
  LPVOID lpArgToCompletionRoutine,   // data value
  DWORD dwTimerLowValue,             // timer low value
  DWORD dwTimerHighValue            // timer high value
)
{
	printf("Time up\n");
}


void main(int argc, char **argv)
{
	HANDLE TimerHandle ;
	LARGE_INTEGER li_dueTime;
	
	TimerHandle = CreateWaitableTimer(NULL, TRUE, "MyTimer");

	li_dueTime.QuadPart = -100000000; // negative times are relative

	SetWaitableTimer(TimerHandle, &li_dueTime, 0, TimeUp, NULL, FALSE);

	// The thread must be in an alertable state for TimeUp routine to be called
	// the second param to SleepEx makes sure that it is so.
	SleepEx(INFINITE, TRUE);
}





