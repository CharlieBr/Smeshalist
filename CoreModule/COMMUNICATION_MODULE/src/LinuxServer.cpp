#include "LinuxServer.h"

LinuxServer::LinuxServer()
{
    clientSocket = createSocket(PORT, &serverAddr);
    SMsocket = createSocket(8393, &SMaddr);

    addr_size = sizeof serverStorage;
    isStopped.store(false);
}

int LinuxServer::createSocket(int port, sockaddr_in* sockAddr) {
    struct timeval tv;
    tv.tv_sec = SOCKET_TIMEOUT_SEC;
    tv.tv_usec = SOCKET_TIMEOUT_NANO;

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("Unable to create UDP socket!!!\n");
        return -1;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Unable to set timeout on socket!!!\n");
    }

    sockAddr -> sin_family = AF_INET;
    sockAddr -> sin_port = htons(port);
    sockAddr -> sin_addr.s_addr = inet_addr(IPADDRESS);
    memset(sockAddr -> sin_zero, '\0', sizeof sockAddr -> sin_zero);

    if (bind(sock, (struct sockaddr *) sockAddr, sizeof(*sockAddr)) < 0) {
        perror("Unable to bind socket!!!\n");
        return -1;
    }

    return sock;
}

void LinuxServer::startServer()
{
    if (t==NULL && SM==NULL) {
        t = new std::thread (&LinuxServer::startServerInNewThread, this);
        SM = new std::thread (&LinuxServer::startSMServer, this);
    }
}

int LinuxServer::getBytesFromSocket(char* buffer, int bufferSize) {
    return recvfrom(clientSocket, buffer, bufferSize, 0, (struct sockaddr *)&serverStorage, &addr_size);
}

int LinuxServer::sendBytesToSocket(char* buffer, int bufferSize) {
    return sendto(clientSocket, buffer, bufferSize, 0, (struct sockaddr *)&serverStorage, addr_size);
}

int LinuxServer::getBytesFromSMsocket(char* buffer, int bufferSize) {
    return recvfrom(SMsocket, buffer, bufferSize, 0, (struct sockaddr *)&SMstorage, &addr_size);
}

int LinuxServer::sendBytesToSMsocket(char* buffer, int bufferSize) {
    return sendto(SMsocket, buffer, bufferSize, 0, (struct sockaddr *)&SMstorage, addr_size);
}

void LinuxServer::stopServer()
{
    if (!isStopped.load()) {
        isStopped.store(true);
        t->join();
        SM->join();
    }
}
