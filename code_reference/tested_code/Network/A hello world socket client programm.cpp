// **********************
/*
		A socket client programm
		connects to port SERVER_PORT on SERVER and 
		sends 1000 bytes of data
*/
// **********************

#include "stdafx.h"
#include <winsock.h>
#include <stdio.h> //printf

#define				SERVICE_PORT			5001
#define				MAX_BUF_LEN				1024
#define				WS_VERSION_REQD			0x0101
#define				WS_VERSION_MAJOR		HIBYTE(WS_VERSION_REQD)
#define				WS_VERSION_MINOR		LOBYTE(WS_VERSION_REQD)
#define				MIN_SOCKETS_REQD		6


/* Static IP address for remote server for example. In reality, this would be    
specified as a hostname or IP address by the user */

#define		SERVER			"63.207.99.83"
#define		SERVER_PORT		5001;   

int main(int argc, char* argv[])
{
	sockaddr_in			srv_addr;
	sockaddr_in			cli_addr;

	SOCKET				cli_sock;

	WSADATA		wsaData;
	int			error;

	error = WSAStartup(WS_VERSION_REQD,&wsaData);

	if (error !=0 ) 
	{
		/* Report that Windows Sockets did not respond to the WSAStartup() call */
		printf("WINSOCK.DLL not responding.");
		exit(1);
	}
	
	if (( LOBYTE (wsaData.wVersion) <	WS_VERSION_MAJOR) || 
		( LOBYTE (wsaData.wVersion) ==	WS_VERSION_MAJOR &&
		HIBYTE (wsaData.wVersion) <		WS_VERSION_MINOR)) 
	{
		/* Report that the application requires Windows Sockets version WS_VERSION_REQD */
		/* compliance and that the WINSOCK.DLL on the system does not support it.       */
		
		printf("Windows Sockets version %d.%d not supported by WINSOCK.DLL",
			LOBYTE (wsaData.wVersion), HIBYTE (wsaData.wVersion));
		exit(1);
	}
	
	if (wsaData.iMaxSockets < MIN_SOCKETS_REQD ) 
	{
		/* Report that WINSOCK.DLL was unable to support the minimum number of  */
		/* sockets (MIN_SOCKETS_REQD) for the application                     */
		printf("This application requires a minimum of %d supported sockets.",
			MIN_SOCKETS_REQD);
		exit(1);
	}

	/* Set up client socket */
		
	cli_sock=socket(PF_INET,SOCK_STREAM,0);
	
	if (cli_sock==INVALID_SOCKET)
	{
		printf("Windows Sockets error %d: Couldn't create socket.",
			WSAGetLastError());
		exit(1);
	}
	
	cli_addr.sin_family=AF_INET;
	cli_addr.sin_addr.s_addr=INADDR_ANY;        
	cli_addr.sin_port=0;                /* no specific port req'd */
	
	/* Bind client socket to any local interface and port */
	
	if (bind(cli_sock,(LPSOCKADDR)&cli_addr,sizeof(cli_addr))==SOCKET_ERROR)
	{
		
		printf("Windows Sockets error %d: Couldn't bind socket.",
			WSAGetLastError());
		exit(1);
	}
	
	
	srv_addr.sin_family			= AF_INET;
	srv_addr.sin_addr.s_addr	= inet_addr(SERVER); 
	srv_addr.sin_port			= SERVER_PORT;
	
	/* Connect to server at address SERVER */
	
	if (connect(cli_sock,(LPSOCKADDR)&srv_addr,sizeof(srv_addr))==SOCKET_ERROR)
	{
		printf("Windows Sockets error %d: Couldn't connect socket.",
			WSAGetLastError());
		exit(1);
	}

	/* Client-server network interaction takes place here */
	int         bytes_sent;
	char        buffer[1000];
	char        *buffer_ptr;
	int         buffer_length;

	sprintf(buffer, "\n******\nHello World\n*******\n");
	
	buffer_ptr		=	buffer;
	buffer_length	=	sizeof(buffer);
	
	// Enter send loop until all data in buffer is sent 
	
	do {
		bytes_sent = send(cli_sock, buffer_ptr, buffer_length, 0);
		if (bytes_sent == SOCKET_ERROR) {
			printf("Windows Sockets error %d: Error while sending data.",
				WSAGetLastError());
			exit(1);
		}
		buffer_ptr += bytes_sent;
		buffer_length -= bytes_sent;
	} while (buffer_length > 0);
	
	return 0;
}
