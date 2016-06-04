#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#define BUFFER_SIZE 1024
#define IPADDRESS "127.0.0.1"
#define PORT 8383
#define SOCKET_TIMEOUT_SEC 1
#define SOCKET_TIMEOUT_NANO 0

#include "Structures.h"
#include "Data.h"
#include <atomic>
#include "../../../CppAPI/structs.pb.h"


class AbstractServer
{
    public:
        AbstractServer(){};
        virtual ~AbstractServer() {};
        virtual void startServer() {};
        virtual void stopServer() {};

        void registerStructuresHandler(Data* data);
    protected:
        virtual void startServerInNewThread() {};

        void parsePoint2DSet(structDefinitions::Point2DSet*);
        void parsePoint3DSet(structDefinitions::Point3DSet*);
        void parseVertexSet(structDefinitions::VertexSet*);
        void parseEdgeSet(structDefinitions::EdgeSet*);
        void parseTriangleFaceSet(structDefinitions::TriangleFaceSet*);
        void parseBlockSet(structDefinitions::BlockSet*);

        Data* handler;
        std::atomic_bool isStopped;
    private:
        Point3D parsePoint(const structDefinitions::Point3D*);
};

#endif // ABSTRACTSERVER_H
