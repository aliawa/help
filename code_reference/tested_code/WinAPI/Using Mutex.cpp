

// ------------------------------------------------------------------------------
// - Using STL queue
// - Using Mutex to synchronize queue access 
// - Tags: Mutex, Queue, STL, Thread, Sleep
// ------------------------------------------------------------------------------

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <queue>

// Using netbufs as queue elements
extern "C"
{
    #include <Ubicom/NetBufApi.h>
}
using namespace std;



// ---------- The Mutex ---------
HANDLE                  g_hMutex              = NULL;

// ---------- The Queue ---------
queue<struct netbuf*>   g_queue;


// ---------- ThreadProc --------
DWORD WINAPI readQueue(LPVOID lpParam)
{
    while(true)
    {
        if (!g_queue.empty())
        {
            // Acquire Mutex
            WaitForSingleObject(g_hMutex,INFINITE );

            struct netbuf* nb = g_queue.front();
            netbuf_set_pos_to_start(nb);
            cout << netbuf_fwd_read_u8(nb) << " ";
            g_queue.pop();
            
            // Release Mutex
            ReleaseMutex(g_hMutex);
        }
        Sleep(1000);
    }
}


// ---------- Main ------------
int main(int argc, char* argv[])
{
    // -------- Create Mutex ------------
    #define OWN_MUTEX               TRUE
    #define DONT_OWN_MUTEX          FALSE
    #define SECURITY_ATTRIBS_NULL   NULL
    g_hMutex = CreateMutex(SECURITY_ATTRIBS_NULL, DONT_OWN_MUTEX, "QueueAccess");
    if (g_hMutex == NULL) 
        cout << "Failed to create mutex" << endl;


    // -------- Create Thread ------------
    DWORD dwThreadId;
    HANDLE hTread;
    hTread = CreateThread(NULL, 0, readQueue, NULL, 0, &dwThreadId);
    if (hTread == NULL) 
        cout << "Failed to create thread" << endl;
    

    // -------- Fill up Queue -------------   
    struct netbuf* nb;
    
    // Acquire Mutex
    WaitForSingleObject(g_hMutex,INFINITE );

    for (u8_t i=0; i<10; ++i)
    {
        nb = netbuf_alloc();
        netbuf_fwd_make_space(nb, 3);
        netbuf_fwd_write_u8(nb, (i+48));
        g_queue.push(nb);
    }

    // Release Mutex
    ReleaseMutex(g_hMutex);

    
   // -------- Do not exit -------------   
    char x;
    cin >> x;

    return 0;
}





