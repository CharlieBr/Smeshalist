#include "AbstractServer.h"

extern int visibleDataTree;
bool transparentStructures = false;

void AbstractServer::registerStructuresHandler(AbstractDataTree* data) {
    if (this->handler != NULL) {
		cout << "Set new data handler\n";
	}

	this->handler = data;
}

void AbstractServer::registerMouseSensitivityHandler(float* pointer) {
    mouseSensitivity = pointer;
}

void AbstractServer::setDynamicRendering(bool flag)
{
	dynamicRendering = flag;
	if (dynamicRendering) {
        sendElementsBufferToTree();
	}
}

void AbstractServer::sendElementsBufferToTree()
{
	for (auto group : elementsBuffer) {
		for (auto type : group.second) {
			handler->add(group.first, &type.second);
		}
	}
	elementsBuffer.clear();
	AbstractDataTree::recomputeIntersectionPointsInVisibleTree(visibleDataTree);
	sendStatistics();
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
    if (handler -> get_min_x() > handler -> get_max_x()) {  //no data in tree - send zeros
        boundingBox.set_fromx(0);  boundingBox.set_tox(0);
        boundingBox.set_fromy(0);  boundingBox.set_toy(0);
        boundingBox.set_fromz(0);  boundingBox.set_toz(0);
    } else {
        boundingBox.set_fromx(handler -> get_min_x());  boundingBox.set_tox(handler-> get_max_x());
        boundingBox.set_fromy(handler -> get_min_y());  boundingBox.set_toy(handler-> get_max_y());
        boundingBox.set_fromz(handler -> get_min_z());  boundingBox.set_toz(handler-> get_max_z());
    }
    (*info.mutable_boundingbox()) = boundingBox;

    //set GroupInfo
    sm::GroupsInfo groupsInfo;
    vector<int>* groups = handler -> get_all_groupIDs();
    for (int id : *groups) {
        Color c = handler -> get_color_for_group(id);
        sm::Color smColor;
        smColor.set_r(c.r()*255);
        smColor.set_g(c.g()*255);
        smColor.set_b(c.b()*255);
        (*groupsInfo.mutable_allgroups())[to_string(id)] = smColor;
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
            singleGroupFilters -> push_back(new SingleGroupFilter(stoi(iter->first), iter -> second));
        }
    }

    if (message -> has_typesfilter()) {
        singleTypeFilters = new vector<SingleTypesFilter*>();
        google::protobuf::Map<string, bool> selectedTypes = (message -> typesfilter()).selectedtypes();
        google::protobuf::Map<string, bool>::iterator iter = selectedTypes.begin();

        for (; iter!=selectedTypes.end(); ++iter) {
            singleTypeFilters -> push_back(new SingleTypesFilter(typeTraslations[iter->first], iter -> second));
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

    AbstractDataTree::reloadFlitersInAllTrees(singleGroupFilters, singleTypeFilters, singleCoordinateFilters, coordinatesConjunction, singleQualityFilters);
    AbstractDataTree::recomputeIntersectionPointsInVisibleTree(visibleDataTree);
    sendStatistics();
}

void AbstractServer::processOptionDataPackage(sm::ManagerToCoreMessage* message) {
    sm::OptionsInfo options = message -> optionsinfo();

    double exponent = options.mousesensitivity();
    *mouseSensitivity = std::pow(BASE, exponent)/BASE;

    setDynamicRendering(options.dynamicrendering());
    //TODO show labels

    transparentStructures = options.transparentstructures();
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
                if (message.has_optionsinfo()) {
                    processOptionDataPackage(&message);
                }
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_SNAPSHOT:
                handler->createNewInstance();
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_CLEAN:
                if (visibleDataTree==-1) {  //clean CURRENT data tree only when it's visible
                    handler->clean();
                    sendStatistics();
                }
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
                sendElementsBufferToTree();
                break;
            case structDefinitions::MessageInfo_Type_CLEAN:
                if (visibleDataTree==-1) {  //clean CURRENT data tree only when it's visible
                    handler->clean();
                    sendStatistics();
                }
                sendAcknowlage();
                break;
            default:
                cerr << "Unknow message type\n";
                break;
        }
    }
}

void AbstractServer::getDataPackages() {
    int nBytes;
    char* buffer;

    while (true) {
        buffer = new char[BUFFER_SIZE];
        nBytes = getBytesFromSocket(buffer, BUFFER_SIZE);
        if (nBytes < 0) {
            cerr << "Error during data package transfer\n";
            return;
        }

        structDefinitions::Header header;
        if (!header.ParseFromArray(buffer, nBytes)) {
            cerr << "Error during parsing header message\n";
            continue;
        }

        structDefinitions::DataPackage package;
        buffer = new char[(int)header.sizeofdata()];
        nBytes = getBytesFromSocket(buffer, header.sizeofdata());

        if (!package.ParseFromArray(buffer, nBytes)) {
            cerr << "Error during parsing data package\n";
            continue;
        }

        parsePoint2DSet(&package);
        parsePoint3DSet(&package);
        parseVertexSet(&package);
        parseEdgeSet(&package);
        parseTriangleFaceSet(&package);
        parseBlockSet(&package);

        sendAcknowlage();

        if(header.endofdata()) {
            break;
        }
    }

    if (dynamicRendering) {
        sendElementsBufferToTree();
	}
}

Point3D AbstractServer::parsePoint(const structDefinitions::Point3D* p) {
    return Point3D(p->x(), p->y(), p->z());
}

Label AbstractServer::getLabel(string text) {
    return Label(text);
}

void AbstractServer::parseBlockSet(structDefinitions::DataPackage* dataPackage) {
	for (int i = 0; i < dataPackage->blocks_size(); i++) {
		const structDefinitions::Block b = dataPackage->blocks(i);
		vector<Point3D> points;

		points.push_back(parsePoint(&b.v1()));
		points.push_back(parsePoint(&b.v2()));
		points.push_back(parsePoint(&b.v3()));
		points.push_back(parsePoint(&b.v4()));

		structDefinitions::Properties prop = b.prop();
		Label label = getLabel(prop.label());

		Block* block = new Block(&points, label, prop.quality());
		elementsBuffer[prop.groupid()][block->get_type()].push_back(block);
	}
}

void AbstractServer::parseEdgeSet(structDefinitions::DataPackage* dataPackage) {
    for (int i=0; i<dataPackage->edges_size(); i++) {
        const structDefinitions::Edge e = dataPackage->edges(i);

        vector<Point3D> points;
        points.push_back(parsePoint(&e.v1()));
        points.push_back(parsePoint(&e.v2()));

        structDefinitions::Properties prop = e.prop();
        Label label = getLabel(prop.label());

        Edge* edge = new Edge(&points, label, prop.quality());
		elementsBuffer[prop.groupid()][edge->get_type()].push_back(edge);
    }
}

void AbstractServer::parsePoint2DSet(structDefinitions::DataPackage* dataPackage) {
    for (int i=0; i<dataPackage->points2d_size(); i++) {
        const structDefinitions::Point2D p = dataPackage->points2d(i);

        structDefinitions::Properties prop = p.prop();
        Label label = getLabel(prop.label());

        Vertex* v = new Vertex(Point3D(p.x(), p.y(), 0), label, prop.quality());
		elementsBuffer[prop.groupid()][v->get_type()].push_back(v);
    }
}

void AbstractServer::parsePoint3DSet(structDefinitions::DataPackage* dataPackage) {
    for (int i=0; i<dataPackage->points3d_size(); i++) {
        const structDefinitions::Point3D p = dataPackage->points3d(i);

        structDefinitions::Properties prop = p.prop();
        Label label = getLabel(prop.label());

        Vertex* v = new Vertex(parsePoint(&p), label, prop.quality());
		elementsBuffer[prop.groupid()][v->get_type()].push_back(v);
    }
}

void AbstractServer::parseTriangleFaceSet(structDefinitions::DataPackage* dataPackage) {
    for (int i=0; i<dataPackage->faces_size(); i++) {
        const structDefinitions::TriangleFace t = dataPackage->faces(i);

        vector<Point3D> points;

        points.push_back(parsePoint(&t.v1()));
        points.push_back(parsePoint(&t.v2()));
        points.push_back(parsePoint(&t.v3()));

        structDefinitions::Properties prop = t.prop();
        Label label = getLabel(prop.label());

        Face* f = new Face(&points, label, prop.quality());
		elementsBuffer[prop.groupid()][f->get_type()].push_back(f);
    }
}

void AbstractServer::parseVertexSet(structDefinitions::DataPackage* dataPackage) {
    for (int i=0; i<dataPackage->vertexes_size(); i++) {
        const structDefinitions::Vertex v = dataPackage->vertexes(i);

        structDefinitions::Properties prop = v.prop();
        Label label = getLabel(prop.label());

        Vertex* vertex = new Vertex(parsePoint(&v.point()), label, prop.quality());
		elementsBuffer[prop.groupid()][vertex->get_type()].push_back(vertex);
    }
}
