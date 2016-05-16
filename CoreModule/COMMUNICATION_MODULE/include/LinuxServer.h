#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <sys/time.h>
#include <atomic>
#include <cerrno>

#include "Structures.h"
#include "Data.h"
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
        std::atomic_bool isStopped;
        std::thread* t;
        Data* handler;

        void startServerInNewThread();
        void registerStructuresHandler(Data*);

        void parsePoint2DSet(structDefinitions::Point2DSet*);
        void parsePoint3DSet(structDefinitions::Point3DSet*);
        void parseVertexSet(structDefinitions::VertexSet*);
        void parseEdgeSet(structDefinitions::EdgeSet*);
        void parseTriangleFaceSet(structDefinitions::TriangleFaceSet*);
        void parseBlockSet(structDefinitions::BlockSet*);
};

#endif // SERVER_H
