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


void LinuxServer::registerStructuresHandler(Data* handler)
{
    if (this->handler != NULL) {
        this->handler = handler;
    }
}

void LinuxServer::parseBlockSet(structDefinitions::BlockSet* blockSet) {

}

void LinuxServer::parseEdgeSet(structDefinitions::EdgeSet* edgeSet) {
    for (int i=0; i<edgeSet->edges_size(); i++) {
        const structDefinitions::Edge e = edgeSet->edges(i);
        Point3D p1(e.v1().x(), e.v1().y(), e.v1().z());
        Point3D p2(e.v2().x(), e.v2().y(), e.v2().z());
        vector<Point3D> points;
        points.push_back(p1);
        points.push_back(p2);
        Edge* edge = new Edge(&points, 0);
        this -> handler -> add(0, edge);
    }
}

void LinuxServer::parsePoint2DSet(structDefinitions::Point2DSet* pointSet) {
    for (int i=0; i<pointSet->points_size(); i++) {
        const structDefinitions::Point2D p = pointSet->points(i);
        Point3D point3D(p.x(), p.y(), 0);
        vector<Point3D> points;
        points.push_back(point3D);
        Vertex* v = new Vertex(&points, 0);
        this -> handler -> add(0, v);
    }
}

void LinuxServer::parsePoint3DSet(structDefinitions::Point3DSet* pointSet) {
    for (int i=0; i<pointSet->points_size(); i++) {
        const structDefinitions::Point3D p = pointSet->points(i);
        Point3D point3D(p.x(), p.y(), p.z());
        vector<Point3D> points;
        points.push_back(point3D);
        Vertex* v = new Vertex(&points, 0);
        this -> handler -> add(0, v);
    }
}

void LinuxServer::parseTriangleFaceSet(structDefinitions::TriangleFaceSet* triangleFaceSet) {
    for (int i=0; i<triangleFaceSet->trianglefaces_size(); i++) {
        const structDefinitions::TriangleFace t = triangleFaceSet->trianglefaces(i);
        //Point3D point3D(p.x(), p.y(), 0);
        /*vector<Point3D> points;
        points.push_back(point3D);
        Vertex* v = new Vertex(&points, 0);
        this -> handler -> add(0, v);*/
    }
}

void LinuxServer::parseVertexSet(structDefinitions::VertexSet* vertexSet) {
    for (int i=0; i<vertexSet->vertexes_size(); i++) {
        const structDefinitions::Vertex v = vertexSet->vertexes(i);
        Point3D point3D(v.point().x(), v.point().y(), v.point().z());
        vector<Point3D> points;
        points.push_back(point3D);
        Vertex* vertex = new Vertex(&points, 0);
        this->handler->add(0, vertex);
    }
}
