// -----------------------------***************----------------------------------
/*			
							Using the Message Loop
						Using ctrl message haendler
*/
// -----------------------------***************----------------------------------

#include "stdafx.h"

#define WIN32_EXTRA_LEAN
#include <windows.h>

DWORD g_dwMainThreadId;

// forward declaration
DWORD WINAPI	ThreadProc	(LPVOID lpParam);
BOOL			CtrlHandler	(DWORD fdwCtrlType) ;

int main(int argc, char* argv[])
{
	DWORD dwThreadId;
	CreateThread(NULL,0,ThreadProc,NULL,0, &dwThreadId);
	
	// used by worker thread to send messages
	g_dwMainThreadId = GetCurrentThreadId();
	
	// Set control haendler to handle ctrl+ key events
	BOOL bSuccess = SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler,  TRUE);
                               
	// init message structure set HWND = NULL -> no window
	MSG msg = {NULL, 0,0,0,0,0};

	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		// translates the virtual-key message into a character message
		// WM_KEYDOWN -> WM_CHAR
		TranslateMessage( &msg );

		// process messages
		switch(msg.message)
		{
		case WM_USER:
			printf("WM_USER Message Received\n");
			break;
		}
		
		// sends msg to the win_proc associated with the window handle
		// specified in MSG.HWND
		// if MSG.HWND  == NULL do nothing
		DispatchMessage( &msg );
	}
	return 0;
}


// *** Theread procedure
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	PostThreadMessage(g_dwMainThreadId, WM_USER, 0,0);	// quit application

	return 1;
}



// *** system message handlers
// override standard ctrl + c handler
BOOL CtrlHandler(DWORD fdwCtrlType) 
{ 
    switch (fdwCtrlType) 
    { 
        // Handle the CTRL+C signal. 
	case CTRL_C_EVENT: 
		
		printf("Ctrl + c pressed ...\n");
		Beep(1000, 1000);
		return TRUE; 
		
        // CTRL+CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		printf("X button on console window pressed ...\n");
		Sleep(2000);
		return TRUE; 
		
        // Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT: 
		printf("Ctrl + Break pressed ...\n");
		Sleep(2000);
		return FALSE; 
	
	case CTRL_LOGOFF_EVENT: 
		printf("User log off initiated ...\n");
		Sleep(2000);
		return FALSE; 

	case CTRL_SHUTDOWN_EVENT: 
		printf("Windows Shutdown ...\n");
		Sleep(2000);
		return FALSE; 

	default: 
		Sleep(2000);
		return FALSE; 
    } 
} 
 