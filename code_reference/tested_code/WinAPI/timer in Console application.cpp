//============================================================================
//
//    Illustrates use of windows SetTimer() when TimerProc() is specified
//         * Every Thread that calls SetTimer() must also dispacth 
//                               windows messages
//                            * Link with user32.lib
//
//============================================================================

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <conio.h>

int		g_nTimerId;
DWORD	g_nMainThreadId;


// A timer proc that can be called three times
// after third call the function kills the timer and 
// ends the application
VOID CALLBACK MyTimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );



int main()
{
	// Set up a 50 millisecond timer which calls MyTimerProc
	g_nTimerId = SetTimer( 0, 0, 0x50, (TIMERPROC)MyTimerProc );
	
	printf( "A timer proc has been set up. Press any key to call "
		"GetMessage/DispatchMessage\n" );
	
	getch();	// Wait for user response. This gives enough time for at
				// least one timer cycle to have elapsed
		
	MSG msg = { 0, 0, 0, 0 };
	
	// store the id of the thread so that the timer proc can send it
	// wm_quit message
	g_nMainThreadId = GetCurrentThreadId();
 
	
	// Get the message, and dispatch it. This causes MyTimerProc to be
	// invoked.
	while ( GetMessage(&msg, 0, 0, 0) )
		DispatchMessage( &msg );
	
	return 0;
	
}



VOID CALLBACK MyTimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
	static i; // counter
	if(++i == 3)
	{
		KillTimer(NULL, g_nTimerId);				// end timer
		PostThreadMessage(g_nMainThreadId, WM_QUIT, 0,0);	// quit application
	}
 
	printf( "In MyTimerProc: hwnd:%X uMsg:%X idEvent:%d dwTime:%d\n",
		hwnd, uMsg, idEvent, dwTime );
}

