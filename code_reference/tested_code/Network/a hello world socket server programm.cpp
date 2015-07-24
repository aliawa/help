// *************************
// A socket server program

// opens a socket at port 5001 and awaits that clients would 
// connect to this server and send 1000 bytes of data
// **************************


#include "stdafx.h"
#include <winsock.h>
#include <stdio.h>		//sprintf

#define				SERVICE_PORT			5001
#define				MAX_BUF_LEN				1024
#define				WS_VERSION_REQD			0x0101
#define				WS_VERSION_MAJOR		HIBYTE(WS_VERSION_REQD)
#define				WS_VERSION_MINOR		LOBYTE(WS_VERSION_REQD)
#define				MIN_SOCKETS_REQD		6


#define				SHOW_MESSAGE(x)		printf("%s", x)
#define				SHOW_MESSAGE_STR(x)	printf(#x "\n")

int main(int argc, char* argv[])
{
	SOCKET				srv_sock;	// server socket
	SOCKET				cli_sock;	// socket opened by accept
	
	struct sockaddr_in	cli_addr;	// will receive client address
	struct sockaddr_in	srv_addr;	// will be filled by the server address
	
	WSADATA		wsaData;
	
	SHOW_MESSAGE_STR(initiate use of WS2_32.DLL);
	int error = WSAStartup(WS_VERSION_REQD,&wsaData);
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
	
	/* Create the server-side socket */
	SHOW_MESSAGE_STR(Create the server-side socket);

	srv_sock = socket(AF_INET,SOCK_STREAM,0);
	
	if (srv_sock==INVALID_SOCKET)
	{
		printf("Windows Sockets error %d: Couldn't create socket.",
			WSAGetLastError());
		exit(1);
	}
	
	srv_addr.sin_family		=	AF_INET;
	srv_addr.sin_addr.s_addr=	INADDR_ANY;
	srv_addr.sin_port		=	SERVICE_PORT;        /* specific port for server to listen on */
	
	/* Bind socket to the appropriate port and interface (INADDR_ANY) */
	SHOW_MESSAGE_STR(Bind socket to the appropriate port and interface);
	if (bind(srv_sock,(LPSOCKADDR)&srv_addr,sizeof(srv_addr))==SOCKET_ERROR)
	{
		printf("Windows Sockets error %d: Couldn't bind socket.",
			WSAGetLastError());
		exit(1);
	}
	
	/* Listen for incoming connections */
	SHOW_MESSAGE_STR(Listen for incoming connections);
	if (listen(srv_sock,1)==SOCKET_ERROR)
	{
		
		printf("Windows Sockets error %d: Couldn't set up listen on socket.",
			WSAGetLastError());
		exit(1);
	}
	
	/* Accept and service incoming connection requests indefinitely */
	SHOW_MESSAGE_STR(Accept and service incoming connection requests indefinitely);
	int addr_len = sizeof(SOCKADDR);
	for ( ; ; ) 
	{
		cli_sock=accept(srv_sock,(LPSOCKADDR)&cli_addr,&addr_len);
		if (cli_sock==INVALID_SOCKET)
		{
			printf("Windows Sockets error %d: Couldn't accept incoming \
				connection on socket.",WSAGetLastError());
			exit(1);
		}
		
		/* Client-server network interaction takes place here */
		char*	buffer_ptr;
		char	buffer[1000];
		int		buffer_length;
		int		bytes_received	= 0;

		buffer_ptr			= buffer;
		buffer_length		= sizeof(buffer);

		/* Receive all outstanding data on socket s */
		
		do {
			bytes_received = recv(cli_sock, buffer_ptr, buffer_length, 0);
			if (bytes_received == SOCKET_ERROR) 
			{
				printf("Windows Sockets error %d: Error while receiving data.",
					WSAGetLastError());
				exit(1);
			}
			buffer_ptr += bytes_received;
			buffer_length -= bytes_received;
		} while (buffer_length > 0);

		SHOW_MESSAGE(buffer);
		
		//Likewise, an application which wants to send 1000 bytes should send() 
		// in a loop until all of the data has been sent:
		
	/*
		SOCKET      s;
		int         bytes_sent;
		char        buffer[1000];
		char        *buffer_ptr;
		int         buffer_length;
		
		buffer_ptr		=	buffer;
		buffer_length	=	sizeof(buffer);
		
		// Enter send loop until all data in buffer is sent 
		
		do {
			bytes_sent = send(s, buffer_ptr, buffer_length, 0);
			if (bytes_sent == SOCKET_ERROR) {
				printf("Windows Sockets error %d: Error while sending data.",
					WSAGetLastError());
				exit(1);
			}
			buffer_ptr += bytes_sent;
			buffer_length -= bytes_sent;
		} while (buffer_length > 0);
		*/
		
		closesocket(cli_sock);
	}
	return 0;
}