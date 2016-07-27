#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <sys/time.h>
#include <cerrno>

#include "AbstractServer.h"

class LinuxServer : public AbstractServer
{
    public:
        LinuxServer();
        void startServer();
        void stopServer();
    private:
        int udpSocket;
        struct sockaddr_in serverAddr;
        socklen_t addr_size;
        struct sockaddr_storage serverStorage;
        std::thread* t = NULL;

        int getBytesFromSocket(char[], int);
        int sendBytesToSocket(char[], int);
};

#endif // SERVER_H
