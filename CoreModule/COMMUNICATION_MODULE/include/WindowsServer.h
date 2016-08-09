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
		int getBytesFromSocket(char[], int);
		int sendBytesToSocket(char[], int);

		SOCKET sock;
		WSADATA wsa;
		struct sockaddr_in sockaddr;
		struct sockaddr client;
		int slen;
		thread* t;
};

#endif // WINDOWSSERVER_H
