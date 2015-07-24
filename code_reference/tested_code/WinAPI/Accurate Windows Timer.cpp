
/* ***************************************************************************

                            Acurate windows Timer
                             Link with winmm.lib

**************************************************************************** */

#include "stdafx.h"

#include <windows.h>
#include <iostream>

using namespace std;



HANDLE g_hEndEvent;

// Call back function for the timer
//
// NOTE :
// Applications should not call any system-defined functions from inside a callback function, 
// except for PostMessage, timeGetSystemTime, timeGetTime, timeSetEvent, timeKillEvent, 
// midiOutShortMsg, midiOutLongMsg, and OutputDebugString.
//
void CALLBACK MyTimerProc( UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    static DWORD dwPrevTime =  timeGetTime();
    static DWORD dwTime;
    static int i=0;
 
    dwTime =  timeGetTime();
    DWORD timeDiff = dwTime - dwPrevTime;
    dwPrevTime = dwTime;

	cout <<  "time-diff: " << timeDiff << endl;
    if (++i == 22) SetEvent(g_hEndEvent);
}



int main(int argc, char* argv[])
{
    // Get minimum and maximum timer resolution for this system
    TIMECAPS tc;
    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
    {
        cout << "error while determining timer resolution" << endl;
        return 1;
    }

    cout << "Timer resolutions for this system:" << endl;  
    cout << "minimum: "<< tc.wPeriodMin << "ms    maximum: " << tc.wPeriodMax<< "ms"<<endl;
    cout << endl;

    // Create an Event for ending the program
    g_hEndEvent = CreateEvent(NULL, TRUE, FALSE, NULL);


    //***  setup a periodic timer with callback function ***//
    UINT uTimerID = timeSetEvent( 10, 1, MyTimerProc, 0,TIME_PERIODIC |TIME_CALLBACK_FUNCTION);

    WaitForSingleObject(g_hEndEvent, INFINITE);

    // Cleanup
    timeKillEvent(uTimerID);
    CloseHandle(g_hEndEvent);

	return 0;
}
