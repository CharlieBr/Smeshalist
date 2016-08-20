#ifndef WINDOWSSERVER_H
#define WINDOWSSERVER_H

#include "AbstractServer.h"

#include <winsock.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")


class WindowsServer : public AbstractServer
{
    public:
        WindowsServer();
        void startServer();
        void stopServer();
    protected:
    private:
		SOCKET* createSocket(sockaddr_in*, int);

		int getBytesFromSocket(char[], int);
		int sendBytesToSocket(char[], int);
		int getBytesFromSMsocket(char[], int);
		int sendBytesToSMsocket(char[], int);

		SOCKET sock;
		SOCKET sockSM;
		WSADATA wsa;
		struct sockaddr_in sockaddr;
		struct sockaddr_in sockaddrSM;
		struct sockaddr client;
		struct sockaddr clientSM;
		int slen;
		thread* t;
		thread* tSM;
};

#endif // WINDOWSSERVER_H
