// ***********************		***********************		
/*	
		Waiting for a thread to terminate
*/
// ***********************		***********************


#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID pParam)
{
	for(int i =0; i<100; ++i)
	{
		for (int j= 0; j<5000000; ++j); // waste time
		printf("%d  ", i);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	DWORD nThreadId;
	HANDLE hThrd = CreateThread(NULL,0,ThreadProc,NULL,0, &nThreadId);
	
	// hThrd is signaled when the thread terminates
	WaitForSingleObject(hThrd,INFINITE);

	return 0;
}
