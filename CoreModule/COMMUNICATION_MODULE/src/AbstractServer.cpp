#include "AbstractServer.h"

void AbstractServer::registerStructuresHandler(AbstractDataTree* data) {
    if (this->handler != NULL) {
		cout << "Set new data handler\n";
	}

	this->handler = data;
}

void AbstractServer::registerMouseSensitivityHandler(float* pointer) {
    mouseSensitivity = pointer;
}

int AbstractServer::sendDatagramToClient(structDefinitions::MessageInfo_Type messageType) {
    char buffer[BUFFER_SIZE];

    structDefinitions::MessageInfo message;
    message.set_type(messageType);

    message.SerializeToArray(buffer, BUFFER_SIZE);

    return sendBytesToSocket(buffer, message.GetCachedSize());
}

void AbstractServer::sendAcknowlage() {
    if (sendDatagramToClient(structDefinitions::MessageInfo_Type_ACK) < 0) {
        cerr << "Error during sending ack to client\n";
    }
}

void AbstractServer::sendContinue() {
    if (sendDatagramToClient(structDefinitions::MessageInfo_Type_ACCEPTED) < 0) {
        cerr << "Error during sending accept to client\n";
    }
}

void AbstractServer::sendAbort(){
    if (sendDatagramToClient(structDefinitions::MessageInfo_Type_REJECTED) < 0) {
        cerr << "Error during sending accept to client\n";
    }
}

void AbstractServer::sendBreakpoint() {
    char buffer[BUFFER_SIZE];

    sm::CoreToManagerMessage message;
    message.set_messagetype(sm::CoreToManagerMessage_CTMMessageType_BREAKPOINT);

    message.SerializeToArray(buffer, BUFFER_SIZE);

    if (sendBytesToSMsocket(buffer, message.GetCachedSize()) < 0) {
        cerr << "Error during sending breakpoint to Smeshalist Manager\n";
    }
}

void AbstractServer::sendStatistics() {
    char buffer[BUFFER_SIZE];

    sm::CoreToManagerMessage message;
    message.set_messagetype(sm::CoreToManagerMessage_CTMMessageType_STATISTICS);
    sm::StatisticsInfo info;

    //set elementsCount
    sm::ElementsCount elementsCount;
    handler -> count_visible_elements();
    Statistics stats = handler -> get_statistics();
    map<string, unsigned long> allElements = stats.all_elements_numbers;
    map<string, unsigned long> visibleElements = stats.visible_elements_numbers;

    for(auto& iter : allElements) {
        sm::ElementInfo elementInfo;
        elementInfo.set_total(iter.second);
        elementInfo.set_visible(visibleElements[iter.first]);
        (*elementsCount.mutable_elementinfos())[iter.first] = elementInfo;
    }
    (*info.mutable_elementscount()) = elementsCount;

    //set boundingBox
    sm::BoundingBox boundingBox;
    boundingBox.set_fromx(handler -> get_min_x());  boundingBox.set_tox(handler-> get_max_x());
    boundingBox.set_fromy(handler -> get_min_y());  boundingBox.set_toy(handler-> get_max_y());
    boundingBox.set_fromz(handler -> get_min_z());  boundingBox.set_toz(handler-> get_max_z());
    (*info.mutable_boundingbox()) = boundingBox;

    //set GroupInfo
    sm::GroupsInfo groupsInfo;
    vector<int>* groups = handler -> get_all_groupIDs();
    for (int id : *groups) {
        groupsInfo.add_allgroups(to_string(id));
    }
    (*info.mutable_groupsinfo()) = groupsInfo;

    (*message.mutable_statisticsinfo()) = info;

    message.SerializeToArray(buffer, BUFFER_SIZE);

    if (sendBytesToSMsocket(buffer, message.GetCachedSize()) < 0) {
        cerr << "Error during sending breakpoint to Smeshalist Manager\n";
    }
}

void AbstractServer::processFiltersDataPackage(sm::ManagerToCoreMessage* message) {
    vector<SingleGroupFilter*> *singleGroupFilters = NULL;
    vector<SingleTypesFilter*> *singleTypeFilters = NULL;
    vector<SingleQualityFilter*> *singleQualityFilters = NULL;
    vector<SingleCoordinateFilter*> *singleCoordinateFilters = NULL;
    LogicalConnectiveEnum* coordinatesConjunction = NULL;


    if (message -> has_groupsfilter()) {
        singleGroupFilters = new vector<SingleGroupFilter*>();
        google::protobuf::Map<string, bool> selectedGroups = (message -> groupsfilter()).selectedgroups();
        google::protobuf::Map<string, bool>::iterator iter = selectedGroups.begin();

        for (; iter!=selectedGroups.end(); ++iter) {
            if (iter -> second) {   //check if group is selected
                int groupID = stoi(iter->first);
                singleGroupFilters -> push_back(new SingleGroupFilter(groupID));
            }
        }
    }

    if (message -> has_typesfilter()) {
        singleTypeFilters = new vector<SingleTypesFilter*>();
        google::protobuf::Map<string, bool> selectedTypes = (message -> typesfilter()).selectedtypes();
        google::protobuf::Map<string, bool>::iterator iter = selectedTypes.begin();

        for (; iter!=selectedTypes.end(); ++iter) {
            if (iter -> second) {   //check if type is selected
                singleTypeFilters -> push_back(new SingleTypesFilter(typeTraslations[iter->first]));
            }
        }
    }

    if (message -> has_qualityfilter()) {
        singleQualityFilters = new vector<SingleQualityFilter*>();

        sm::QualityFilter filter = message -> qualityfilter();
        int size = filter.qualitycondition_size();

        for (int i=0; i<size; i++) {
            sm::QualityCondition condition = filter.qualitycondition(i);

            Double* leftValue = NULL;
            Double* rightValue = NULL;
            RelationalOperator leftOp;
            RelationalOperator rightOp;

            if (condition.has_leftvalue()) {
                leftValue = new Double(condition.leftvalue());
                leftOp = operatorTranslations[condition.leftoperator()];
            }
            if (condition.has_rightvalue()) {
                rightValue = new Double(condition.rightvalue());
                rightOp = operatorTranslations[condition.rightoperator()];
            }
            SingleQualityFilter* qualityFilter = new SingleQualityFilter(leftValue, leftOp, rightOp, rightValue);
            singleQualityFilters -> push_back(qualityFilter);
        }
    }

    if (message -> has_coordinatesfilter()) {
        singleCoordinateFilters = new vector<SingleCoordinateFilter*>();
        sm::CoordinatesFilter filter = message -> coordinatesfilter();

        if (filter.has_conjunction()) {
            coordinatesConjunction = &conjunctionTranslations[filter.conjunction()];
        }

        int size = filter.coordinatescondition_size();
        for (int i=0; i<size; i++) {
            sm::CoordinatesCondition condition = filter.coordinatescondition(i);

            SingleCoordinateFilter* coordFilter = new SingleCoordinateFilter(   condition.xvalue(),
                                                                                condition.yvalue(),
                                                                                condition.zvalue(),
                                                                                condition.constant(),
                                                                                operatorTranslations[condition.coordinatesoperator()]);
            singleCoordinateFilters -> push_back(coordFilter);
        }
    }

    handler -> reloadFliters(singleGroupFilters, singleTypeFilters, singleCoordinateFilters, coordinatesConjunction, singleQualityFilters);
    sendStatistics();
}

void AbstractServer::processOptionDataPackage(sm::ManagerToCoreMessage* message) {
    sm::OptionsInfo options = message -> optionsinfo();

    double exponent = options.mousesensitivity();
    *mouseSensitivity = std::pow(BASE, exponent)/BASE;

    //TODO dynamic rendering
    //TODO show labels
    //TODO transparent structures
}

void AbstractServer::startSMServer() {
    int nBytes;
    char buffer[BUFFER_SIZE];

    while(!isStopped.load()){
        nBytes = getBytesFromSMsocket(buffer, BUFFER_SIZE);
        if (nBytes < 0) {
            continue;
        }

        sm::ManagerToCoreMessage message;
        if (!message.ParseFromArray(buffer, nBytes)) {
            cerr << "Unable to parse message from SmeshalistManager\n";
            continue;
        }

        switch (message.messagetype()) {
            case sm::ManagerToCoreMessage_MTCMessageType_ABORT:
                sendAbort();
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_CONTINUE:
                sendContinue();
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_FILTERS:
                processFiltersDataPackage(&message);
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_OPTIONS:
                processOptionDataPackage(&message);
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_HELLO:
                //SM connected
                break;
            default:
                cerr << "Unknow message type\n";
                break;
        }
    }
}

void AbstractServer::startServerInNewThread()
{
    int nBytes;
    char buffer[BUFFER_SIZE];

    while(!isStopped.load()){
        nBytes = getBytesFromSocket(buffer, BUFFER_SIZE);
        if (nBytes < 0) {
            continue;
        }

        structDefinitions::MessageInfo messageInfo;
        if (!messageInfo.ParseFromArray(buffer, nBytes)) {
            cerr << "Unable to parse messageInfo\n";
            continue;
        }

        switch (messageInfo.type()) {
            case structDefinitions::MessageInfo_Type_DATA:
                sendAcknowlage();
                getDataPackages();
                handler -> draw_elements();
                break;
            case structDefinitions::MessageInfo_Type_BREAKPOINT:
                sendBreakpoint();
                break;
            case structDefinitions::MessageInfo_Type_RENDER:
                cout << "Render\n";
                break;
            default:
                cerr << "Unknow message type\n";
                break;
        }
    }
}

void AbstractServer::getDataPackages() {
    char buffer[BUFFER_SIZE];
    int nBytes;

    while (true) {
        nBytes = getBytesFromSocket(buffer, BUFFER_SIZE);
        if (nBytes < 0) {
            cerr << "Error during data package transfer\n";
            return;
        }

        structDefinitions::DataPackage package;

        if (!package.ParseFromArray(buffer, nBytes)) {
            cerr << "Error during parsing data package\n";
            continue;
        }

        if (package.has_blocks()) {
            structDefinitions::BlockSet blockSet = package.blocks();
            parseBlockSet(&blockSet);
        }

        if (package.has_edges()) {
            structDefinitions::EdgeSet edgeSet = package.edges();
            parseEdgeSet(&edgeSet);
        }

        if (package.has_faces()) {
            structDefinitions::TriangleFaceSet faceSet = package.faces();
            parseTriangleFaceSet(&faceSet);
        }

        if (package.has_points2d()) {
            structDefinitions::Point2DSet pointSet = package.points2d();
            parsePoint2DSet(&pointSet);
        }

        if (package.has_points3d()) {
            structDefinitions::Point3DSet pointSet = package.points3d();
            parsePoint3DSet(&pointSet);
        }

        if (package.has_vertexes()) {
            structDefinitions::VertexSet vertexSet = package.vertexes();
            parseVertexSet(&vertexSet);
        }

        if(package.endofdata()) {
            break;
        }
    }

    sendStatistics();
}

Point3D AbstractServer::parsePoint(const structDefinitions::Point3D* p) {
    return Point3D(p->x(), p->y(), p->z());
}

Label AbstractServer::getLabel(string text) {
    return Label(text);
}

void AbstractServer::parseBlockSet(structDefinitions::BlockSet* blockSet) {
    for(int i=0; i<blockSet->blocks_size(); i++) {
        const structDefinitions::Block b = blockSet->blocks(i);
        vector<Point3D> points;
        vector<Face> faces;

        points.push_back(parsePoint(&b.v1()));
        points.push_back(parsePoint(&b.v2()));
        points.push_back(parsePoint(&b.v3()));
        points.push_back(parsePoint(&b.v4()));

        structDefinitions::Properties prop = b.prop();
        Label label = getLabel(prop.label());

        Block* block = new Block(&points, label, prop.quality());
        this -> handler -> add(prop.groupid(), block);
    }
}

void AbstractServer::parseEdgeSet(structDefinitions::EdgeSet* edgeSet) {
    for (int i=0; i<edgeSet->edges_size(); i++) {
        const structDefinitions::Edge e = edgeSet->edges(i);

        vector<Point3D> points;
        points.push_back(parsePoint(&e.v1()));
        points.push_back(parsePoint(&e.v2()));

        structDefinitions::Properties prop = e.prop();
        Label label = getLabel(prop.label());

        Edge* edge = new Edge(&points, label, prop.quality());
        this -> handler -> add(prop.groupid(), edge);
    }
}

void AbstractServer::parsePoint2DSet(structDefinitions::Point2DSet* pointSet) {
    for (int i=0; i<pointSet->points_size(); i++) {
        const structDefinitions::Point2D p = pointSet->points(i);

        structDefinitions::Properties prop = p.prop();
        Label label = getLabel(prop.label());

        Vertex* v = new Vertex(Point3D(p.x(), p.y(), 0), label, prop.quality());
        this -> handler -> add(prop.groupid(), v);
    }
}

void AbstractServer::parsePoint3DSet(structDefinitions::Point3DSet* pointSet) {
    for (int i=0; i<pointSet->points_size(); i++) {
        const structDefinitions::Point3D p = pointSet->points(i);

        structDefinitions::Properties prop = p.prop();
        Label label = getLabel(prop.label());

        Vertex* v = new Vertex(parsePoint(&p), label, prop.quality());
        this -> handler -> add(prop.groupid(), v);
    }
}

void AbstractServer::parseTriangleFaceSet(structDefinitions::TriangleFaceSet* triangleFaceSet) {
    for (int i=0; i<triangleFaceSet->trianglefaces_size(); i++) {
        const structDefinitions::TriangleFace t = triangleFaceSet->trianglefaces(i);

        vector<Point3D> points;

        points.push_back(parsePoint(&t.v1()));
        points.push_back(parsePoint(&t.v2()));
        points.push_back(parsePoint(&t.v3()));

        structDefinitions::Properties prop = t.prop();
        Label label = getLabel(prop.label());

        Face* f = new Face(&points, label, prop.quality());
        this -> handler -> add(prop.groupid(), f);
    }
}

void AbstractServer::parseVertexSet(structDefinitions::VertexSet* vertexSet) {
    for (int i=0; i<vertexSet->vertexes_size(); i++) {
        const structDefinitions::Vertex v = vertexSet->vertexes(i);

        structDefinitions::Properties prop = v.prop();
        Label label = getLabel(prop.label());

        Vertex* vertex = new Vertex(parsePoint(&v.point()), label, prop.quality());
        this->handler->add(prop.groupid(), vertex);
    }
}
