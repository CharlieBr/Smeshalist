#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <sys/time.h>

#include "../structs.pb.h"

#define BUFFER_SIZE 1024
#define IPADDRESS "127.0.0.1"
#define PORT 8383
#define SOCKET_TIMEOUT_SEC 1
#define SOCKET_TIMEOUT_NANO 0

class Server
{
    public:
        Server();
        void startServer();
        void stopServer();
    private:
        int udpSocket;
        struct sockaddr_in serverAddr;
        socklen_t addr_size;
        struct sockaddr_storage serverStorage;
        bool isStopped;
        std::thread t;

        void startServerInNewThread();
};

#endif // SERVER_H
