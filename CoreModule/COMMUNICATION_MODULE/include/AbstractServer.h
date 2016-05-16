#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#define BUFFER_SIZE 1024
#define IPADDRESS "127.0.0.1"
#define PORT 8383
#define SOCKET_TIMEOUT_SEC 1
#define SOCKET_TIMEOUT_NANO 0

#include "../../../CppAPI/structs.pb.h"


class AbstractServer
{
    public:
        AbstractServer(){};
        virtual ~AbstractServer() {};
        virtual void startServer() {};
        virtual void stopServer() {};
        virtual void registerStructuresHandler(Data*) {};
        virtual void parsePoint2DSet(structDefinitions::Point2DSet*) {};
        virtual void parsePoint3DSet(structDefinitions::Point3DSet*) {};
        virtual void parseVertexSet(structDefinitions::VertexSet*) {};
        virtual void parseEdgeSet(structDefinitions::EdgeSet*) {};
        virtual void parseTriangleFaceSet(structDefinitions::TriangleFaceSet*) {};
        virtual void parseBlockSet(structDefinitions::BlockSet*) {};
    protected:
        virtual void startServerInNewThread() {};
    private:
};

#endif // ABSTRACTSERVER_H
