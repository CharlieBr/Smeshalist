#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#define BUFFER_SIZE 1024*2
#define IPADDRESS "127.0.0.1"
#define PORT 8383
#define SOCKET_TIMEOUT_SEC 1
#define SOCKET_TIMEOUT_NANO 0

#include "Structures.h"
#include "Data.h"
#include <atomic>
#include "structs.pb.h"
#include "communication.pb.h"


class AbstractServer
{
    public:
        AbstractServer(){};
        virtual ~AbstractServer() {};
        virtual void startServer() {};
        virtual void stopServer() {};

        void registerStructuresHandler(Data* data);
    protected:
        virtual int getBytesFromSocket(char[], int) = 0;
        virtual int sendBytesToSocket(char[], int) = 0;
        virtual int getBytesFromSMsocket(char[], int) = 0;
        virtual int sendBytesToSMsocket(char[], int) = 0;

        void parsePoint2DSet(structDefinitions::Point2DSet*);
        void parsePoint3DSet(structDefinitions::Point3DSet*);
        void parseVertexSet(structDefinitions::VertexSet*);
        void parseEdgeSet(structDefinitions::EdgeSet*);
        void parseTriangleFaceSet(structDefinitions::TriangleFaceSet*);
        void parseBlockSet(structDefinitions::BlockSet*);

        void getDataPackages();
        void processFiltersDataPackage(sm::ManagerToCoreMessage);
        int sendDatagramToClient(structDefinitions::MessageInfo_Type);
        void sendAcknowlage();
        void startServerInNewThread();
        void startSMServer();

        void sendContinue();
        void sendAbort();

        void sendBreakpoint();

        Data* handler = NULL;
        std::atomic_bool isStopped;
    private:
        Point3D parsePoint(const structDefinitions::Point3D*);
        Label getLabel(string);
};

#endif // ABSTRACTSERVER_H
