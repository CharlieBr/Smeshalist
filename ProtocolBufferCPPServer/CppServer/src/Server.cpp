#include "Server.h"

Server::Server()
{
    struct timeval tv;
    tv.tv_sec = SOCKET_TIMEOUT_SEC;
    tv.tv_usec = SOCKET_TIMEOUT_NANO;

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Unable to set timeout on socket!!!");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IPADDRESS);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    addr_size = sizeof serverStorage;
    isStopped = false;
}

void Server::startServer()
{
    //t = std::thread (&Server::startServerInNewThread, this);
    //TODO: fixed problems with compilator/linker
    startServerInNewThread();
}

void Server::startServerInNewThread()
{
    int nBytes;
    char buffer[BUFFER_SIZE];

    while(!isStopped){
        nBytes = recvfrom(udpSocket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&serverStorage, &addr_size);

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

void Server::stopServer()
{
    isStopped = true;
    //t.join();
}
