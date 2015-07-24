// ---------------**********************************--------------
//
//		create a mail slot and read messages written to the 
//		slot
//		
//		if a client is in the same DOMAIN and same WORKGROUP
//		broadcasts to slot named X can be read by any servers
//		that have opened a slot named X
// ---------------**********************************--------------


#include <windows.h>
#include <stdio.h>
#include <conio.h>

HANDLE hSlot1;

bool FAR PASCAL Makeslot() 
{ 
    char* lpszSlotName = "\\\\.\\mailslot\\myslt";  // --> \.\mailslot\myslt
	
    // The mailslot handle "hSlot1" is declared globally. 
	
    hSlot1 = CreateMailslot(lpszSlotName, 
        0,                             // no maximum message size 
        MAILSLOT_WAIT_FOREVER,         // no time-out for operations 
        (LPSECURITY_ATTRIBUTES) NULL); // no security attributes 
	
    if (hSlot1 == INVALID_HANDLE_VALUE) 
    { 
        printf("CreateMailslot failed\n"); // local error handler 
        return FALSE; 
    } 
	
	printf("CreateMailSlot successful\n");
    return true; 
} 




BOOL WINAPI Readslot() 
{ 
    DWORD nMessageSize  = 0;
	DWORD nMessageCount = 0; 
	DWORD nBytesRead	= 0; 
    DWORD nNoOfMessages;

	LPSTR lpszBuffer;
	BOOL  bResult;
 
    // Mailslot handle "hSlot1" is declared globally. 
 
    bResult = GetMailslotInfo(hSlot1, // mailslot handle 
        (LPDWORD) NULL,               // no maximum message size 
        &nMessageSize,                // size of next message 
        &nMessageCount,               // number of messages 
        (LPDWORD) NULL);              // no read time-out 
 
    if (!bResult) 
    { 
        printf("GetMailslotInfo failed\n"); 
        return FALSE; 
    } 
 
    if (nMessageSize == MAILSLOT_NO_MESSAGE) 
    { 
        printf("No waiting messages.\n"); 
        return TRUE; 
    } 
 
    nNoOfMessages = nMessageCount; 
 
    // call GetMailSlotInfo repeatedly to determine 
	//	1. the number of remaining messages
	//  2. size of the next message
	//	3. allocate memory
	//	4. read into the allocated buffer using ReadFile
	
	while (nMessageCount != 0)  // retrieve all messages
    { 
        // Allocate memory for the message.
		// GPTR will initilize the contents to zero
		
		lpszBuffer = (LPSTR) GlobalAlloc(GPTR, nMessageSize); 
        // the above line can be replace by 
		// lpszBuffer = new char[nMessageSize + 1];
		// in win32 there is no difference between GlobalAlloc
		// and LocalAlloc (era of FAR and NEAR ptrs);

		
		bResult = ReadFile(hSlot1, 
            lpszBuffer,					// buffer to hold the message
            nMessageSize,				// size of buffer
            &nBytesRead,				// bytes actually read
            (LPOVERLAPPED) NULL); 
		
        if (!bResult) 
        { 
            printf("ReadFile faled\n"); 
            GlobalFree((HGLOBAL) lpszBuffer); 
            return FALSE; 
        } 
		
		
		// Display the message. 
		printf("\nMessage #%d of %d :  %s", 
			nNoOfMessages - nMessageCount + 1, 
            nNoOfMessages,
			lpszBuffer); 
		
        GlobalFree((HGLOBAL) lpszBuffer); 
		
        bResult = GetMailslotInfo(hSlot1, // mailslot handle 
            (LPDWORD) NULL,               // no maximum message size 
            &nMessageSize,                // size of next message 
            &nMessageCount,               // number of messages 
            (LPDWORD) NULL);              // no read time-out 
		
        if (!bResult) 
        { 
            printf("GetMailslotInfo failed\n"); 
            return FALSE; 
        } 
    } 
    return TRUE; 
} 



int main(int argc, char* argv[])
{
	Makeslot();
	
	while(getch() != 'c')
	{
		Readslot();
	}

	return 0;
}
