// --------
// given an IP address in dotted decimal format as a string
// how to get the HOSTENT structure
// --------

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>     // for fprintf and stderr

int main(int argc, char* argv[])
{
    unsigned int    addr; 
    struct hostent* hp; 
    char*           server_name= "192.168.1.123"; 
    
    // initialize winsock dll (no error checking here)
    WORD wVersionRequested = MAKEWORD( 2, 2 );
    WSADATA wsaData;
    int err;
    err = WSAStartup( wVersionRequested, &wsaData );


    // Attempt to detect if we should call gethostbyname() or gethostbyaddr()  
    if (isalpha(server_name[0])) 
    {   
        /* server address is a name */ 
        hp = gethostbyname(server_name); 
    } 
    else  
    { 
        /* Convert nnn.nnn address to a usable one */ 
        addr = inet_addr(server_name); 
        hp   = gethostbyaddr((char *)&addr,4,AF_INET); 
    } 
    
    if (hp == NULL ) 
    { 
        fprintf(stderr,"Client: Cannot resolve address [%s]: Error %d\n", server_name,WSAGetLastError()); WSACleanup(); 
        exit(1); 
    } 

    return 1;
}
