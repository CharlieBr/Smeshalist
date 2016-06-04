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
        //POINT 2D
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);
        if (nBytes < 0) {
            continue;
        }

        structDefinitions::Point2DSet point2DSet;
        if(!point2DSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse Point2D\n");
        }
        parsePoint2DSet(&point2DSet);

        //POINT 3D
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);
        if (nBytes < 0) {
            continue;
        }
        structDefinitions::Point3DSet point3DSet;
        if(!point3DSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse Point3D\n");
        }
        parsePoint3DSet(&point3DSet);

        //VERTEX
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);
        if (nBytes < 0) {
            continue;
        }
        structDefinitions::VertexSet vertexSet;
        if(!vertexSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse Vertex\n");
        }

        parseVertexSet(&vertexSet);

        //EDGE
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);
        if (nBytes < 0) {
            continue;
        }
        structDefinitions::EdgeSet edgeSet;
        if(!edgeSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse Edge\n");
        }
        parseEdgeSet(&edgeSet);

        //FACE
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);
        if (nBytes < 0) {
            continue;
        }
        structDefinitions::TriangleFaceSet faceSet;
        if(!faceSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse Triangle\n");
        }
        parseTriangleFaceSet(&faceSet);

        //BLOCK
        nBytes = recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverStorage, &addr_size);
        if (nBytes < 0) {
            continue;
        }
        structDefinitions::BlockSet blockSet;
        if(!blockSet.ParseFromArray(buffer, nBytes)) {
            printf("Unable to parse Block\n");
        }
        parseBlockSet(&blockSet);

        this -> handler -> draw_elements();
    }
}

void LinuxServer::stopServer()
{
    if (!isStopped.load()) {
        isStopped.store(true);
        t->join();
    }
}
