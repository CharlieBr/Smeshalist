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
        int clientSocket;
        int SMsocket;
        struct sockaddr_in serverAddr;
        struct sockaddr_in SMaddr;
        socklen_t addr_size;
        struct sockaddr_storage serverStorage;
        struct sockaddr_storage SMstorage;
        std::thread* t = NULL;
        std::thread* SM = NULL;

        int getBytesFromSocket(char[], int);
        int sendBytesToSocket(char[], int);
        int getBytesFromSMsocket(char[], int);
        int sendBytesToSMsocket(char[], int);

        int createSocket(int, sockaddr_in*);
};

#endif // SERVER_H
