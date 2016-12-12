#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#define BUFFER_SIZE 1024*2
#define BASE 4
#define IPADDRESS "127.0.0.1"
#define SOCKET_TIMEOUT_SEC 10
#define SOCKET_TIMEOUT_NANO 0

#include "Structures.h"
#include "AbstractDataTree.h"
#include <atomic>
#include "structs.pb.h"
#include "communication.pb.h"
#include "UserPreferencesManager.h"
#include "OBJExporter.h"
#include "OBJImporter.h"



class AbstractServer
{
    public:
        AbstractServer(){
            typeTraslations["Vertex"] = "vertex";
            typeTraslations["Edge"] = "edge";
            typeTraslations["Face"] = "face";
            typeTraslations["Block"] = "block";

            conjunctionTranslations[sm::CoordinatesFilter_Conjunction_AND] = LogicalConnectiveEnum::AND;
            conjunctionTranslations[sm::CoordinatesFilter_Conjunction_OR] = LogicalConnectiveEnum::OR;

            operatorTranslations[sm::ComparisonOperator::EQUAL] = RelationalOperator::eq;
            operatorTranslations[sm::ComparisonOperator::GREATER] = RelationalOperator::gt;
            operatorTranslations[sm::ComparisonOperator::GREATER_OR_EQUAL] = RelationalOperator::ge;
            operatorTranslations[sm::ComparisonOperator::LESS] = RelationalOperator::lt;
            operatorTranslations[sm::ComparisonOperator::LESS_OR_EQUAL] = RelationalOperator::le;

            PORT = UserPreferencesManager::getInstance() -> getCorePort();
        };
        virtual ~AbstractServer() {};
        virtual void startServer() {};
        virtual void stopServer() {};

        void registerStructuresHandler(AbstractDataTree*);
        void registerMouseSensitivityHandler(float*);
		void setDynamicRendering(bool);
		void sendElementsBufferToTree();
		void sendStatistics();
		void sendStatisticsOfCurrentlyVisibleTree();
		bool isOrthoViewSet();
    protected:
        virtual int getBytesFromSocket(char[], int) = 0;
        virtual int sendBytesToSocket(char[], int) = 0;
        virtual int getBytesFromSMsocket(char[], int) = 0;
        virtual int sendBytesToSMsocket(char[], int) = 0;

        void parsePoint3DSet(structDefinitions::DataPackage*);
        void parseVertexSet(structDefinitions::DataPackage*);
        void parseEdgeSet(structDefinitions::DataPackage*);
        void parseTriangleFaceSet(structDefinitions::DataPackage*);
        void parseBlockSet(structDefinitions::DataPackage*);

        void changeVisibleTree();

        void getDataPackages();
        void processFiltersDataPackage(sm::ManagerToCoreMessage*);
        void processOptionDataPackage(sm::ManagerToCoreMessage*);
        void processDataImportMessage(sm::ManagerToCoreMessage*);
        void processDataExportMessage(sm::ManagerToCoreMessage*);
        int sendDatagramToClient(structDefinitions::MessageInfo_Type);
        void sendAcknowlage();
        void sendStaticticsOfGivenTree(AbstractDataTree*);
        void startServerInNewThread();
        void startSMServer();

        void sendContinue();
        void sendAbort();

        void sendBreakpoint();

        AbstractDataTree* handler = NULL;
        OBJExporter exporter;
        OBJImporter importer;
        int PORT;
        float* mouseSensitivity;
        std::atomic_bool isStopped;
        std::map<string, string> typeTraslations;
        std::map<sm::CoordinatesFilter_Conjunction, LogicalConnectiveEnum> conjunctionTranslations;
        std::map<sm::ComparisonOperator, RelationalOperator> operatorTranslations;
    private:
        Point3D parsePoint(const structDefinitions::Point3D*);
        Label getLabel(string);
		map<int, map<string, vector<Element*>>> elementsBuffer;
		bool dynamicRendering = true;
		bool isOrtho = false;
};

#endif // ABSTRACTSERVER_H
