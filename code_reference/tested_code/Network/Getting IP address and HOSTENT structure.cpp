//
// How to get IP address from a host name.
//

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>    // for fprintf and stderr


int main(int argc, char* argv[])
{
    // initialize winsock
    WSADATA            wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup() failed: %d\n", GetLastError());
        return 1;
    }

    
    //-------------------------------------------------------------------------
    //Getting the ip of local maschine in windows
    //
    //
    char Buffer[24]; //A pointer to a buffer that receives the local host name. 
    
    // get the host name e.g. "albab"
    gethostname(Buffer,24);

    // get the IP address in the form of a HOSTENT structure
    struct hostent* hAddr = gethostbyname(&Buffer[0]);
    
    // h_addr_list is a NULL-terminated list of addresses for the host
    // the data type of the list is char*
    // we take the first address from the list
    ULONG nIPAddress = *((ULONG *)hAddr->h_addr_list[0]); 
    



    
    //-------------------------------------------------------------------------
    //Getting the ip of any machine if its name is known
    //
    //
    char* host_name = "SC-Engr";            // we want to find the ip address of SC-Engr
    
    // this call will result in an NBNS name query
    hAddr = gethostbyname(host_name);
    
    // h_addr_list is a NULL-terminated list of addresses for the host
    // the data type of the list is char*
    // we take the first address from the list
    nIPAddress = *((ULONG *)hAddr->h_addr_list[0]); 
    




    //-------------------------------------------------------------------------
    //Getting the HOSTENT structure from server name or dotted decimal address
    //
    //    
    unsigned int    addr; 
    host_name= "localhost"; // or host_name = "192.168.1.111"
    
    // Attempt to detect if we should call gethostbyname() or gethostbyaddr()  
    if (isalpha(host_name[0])) 
    {   
        // address is a name 
        hAddr = gethostbyname(host_name); 
    } 
    else  
    { 
        // Convert the string "nnn.nnn.nnn.nnn" to an integer
        addr = inet_addr(host_name); 

        hAddr= gethostbyaddr((char *)&addr,4,AF_INET); 
    } 
    
    if (hAddr == NULL ) 
    { 
        fprintf(stderr,"Client: Cannot resolve address [%s]: Error %d\n", host_name,WSAGetLastError()); WSACleanup(); 
        exit(1); 
    } 
    


    return 0;
}
