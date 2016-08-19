#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#define BUFFER_SIZE 1024*2
#define BASE 4
#define IPADDRESS "127.0.0.1"
#define PORT 8383
#define SOCKET_TIMEOUT_SEC 1
#define SOCKET_TIMEOUT_NANO 0

#include "Structures.h"
#include "AbstractDataTree.h"
#include <atomic>
#include "structs.pb.h"
#include "communication.pb.h"


class AbstractServer
{
    public:
        AbstractServer(){
            typeTraslations["Vertexes"] = "vertex";
            typeTraslations["Edges"] = "edge";
            typeTraslations["Triangles"] = "face";
            typeTraslations["Pyramids"] = "block";

            conjunctionTranslations[sm::CoordinatesFilter_Conjunction_AND] = LogicalConnectiveEnum::AND;
            conjunctionTranslations[sm::CoordinatesFilter_Conjunction_OR] = LogicalConnectiveEnum::OR;

            operatorTranslations[sm::ComparisonOperator::EQUAL] = RelationalOperator::eq;
            operatorTranslations[sm::ComparisonOperator::GREATER] = RelationalOperator::gt;
            operatorTranslations[sm::ComparisonOperator::GREATER_OR_EQUAL] = RelationalOperator::ge;
            operatorTranslations[sm::ComparisonOperator::LESS] = RelationalOperator::lt;
            operatorTranslations[sm::ComparisonOperator::LESS_OR_EQUAL] = RelationalOperator::le;
        };
        virtual ~AbstractServer() {};
        virtual void startServer() {};
        virtual void stopServer() {};

        void registerStructuresHandler(AbstractDataTree*);
        void registerMouseSensitivityHandler(float*);
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
        void processFiltersDataPackage(sm::ManagerToCoreMessage*);
        void processOptionDataPackage(sm::ManagerToCoreMessage*);
        int sendDatagramToClient(structDefinitions::MessageInfo_Type);
        void sendAcknowlage();
        void startServerInNewThread();
        void startSMServer();

        void sendContinue();
        void sendAbort();

        void sendBreakpoint();
        void sendStatistics();

        AbstractDataTree* handler = NULL;
        float* mouseSensitivity;
        std::atomic_bool isStopped;
        std::map<string, string> typeTraslations;
        std::map<sm::CoordinatesFilter_Conjunction, LogicalConnectiveEnum> conjunctionTranslations;
        std::map<sm::ComparisonOperator, RelationalOperator> operatorTranslations;
    private:
        Point3D parsePoint(const structDefinitions::Point3D*);
        Label getLabel(string);
};

#endif // ABSTRACTSERVER_H
