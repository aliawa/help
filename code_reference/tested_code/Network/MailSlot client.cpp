//
//	------------------*******************************------------------
//		broadcasting a message on a mail slot
//
//		1.  All servers on the same DOMAIN and same WORKGROUP
//			can read the broadcasted message from the mail slot
//	------------------******************************------------------
//


#include "stdafx.h"
#include <windows.h>
#include "stdio.h"
#include <conio.h>


bool Writeslot(HANDLE hFile, char* lpszMessage)
{
	DWORD cbWritten;
	
	bool fResult = WriteFile(hFile, 
		lpszMessage, 
		(DWORD) lstrlen(lpszMessage) + 1,  // include terminating null 
		&cbWritten, 
		(LPOVERLAPPED) NULL); 
	
	if (!fResult) 
	{ 
		printf("WriteFile failed\n"); 
		return false; 
	} 
	
	printf("WriteFile successful\n"); 
	
	return true; 
}
 

int main(int argc, char* argv[])
{
	HANDLE hFile = CreateFile("\\\\*\\mailslot\\myslt", 
		GENERIC_WRITE, 
		FILE_SHARE_READ,				// required to write to a mailslot 
		(LPSECURITY_ATTRIBUTES) NULL,	// handle cannot be inherited
		OPEN_EXISTING,					// dont try to create the file
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
	
	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		printf("CreateFile failed\n"); // local error handler 
		return false; 
	} 

	while(getch() != 'c')
	{
		Writeslot(hFile, "** Hello World **\n");
	}

	BOOL fResult = CloseHandle(hFile); 
	
	if (!fResult) 
	{ 
		printf("CloseHandle failed\n"); 
		return FALSE; 
	} 
	
	printf("CloseHandle successful.\n"); 

	return 0;
}
