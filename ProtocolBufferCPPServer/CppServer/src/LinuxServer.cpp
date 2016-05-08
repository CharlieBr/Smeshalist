#include "LinuxServer.h"

LinuxServer::LinuxServer()
{
    struct timeval tv;
    tv.tv_sec = SOCKET_TIMEOUT_SEC;
    tv.tv_usec = SOCKET_TIMEOUT_NANO;

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    if (udpSocket < 0) {
        perror("Unable to create UDP socket!!!\n");
        return;
    }

    if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Unable to set timeout on socket!!!\n");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IPADDRESS);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    if (bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Unable to bind socket!!!\n");
        return;
    }

    addr_size = sizeof serverStorage;
    isStopped.store(false);
}

void LinuxServer::startServer()
{
    if (t==NULL) {
        t = new std::thread (&LinuxServer::startServerInNewThread, this);
    }
}

void LinuxServer::startServerInNewThread()
{
    int nBytes;
    char buffer[BUFFER_SIZE];

    while(!isStopped.load()){
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);

        if (nBytes < 0) {
            continue;
        }

        Point2DSet pointSet;
        if(!pointSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse\n");
        }

        for (int i=0; i<pointSet.points_size(); i++) {
            const Point2D p = pointSet.points(i);
            printf("Point2D [%f , %f]\n", p.x(), p.y());
        }
    }
}

void LinuxServer::stopServer()
{
    if (!isStopped.load()) {
        isStopped.store(true);
        t->join();
    }
}
