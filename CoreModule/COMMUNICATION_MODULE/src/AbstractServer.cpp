#include "AbstractServer.h"

bool transparentStructures = false;
bool showLabels = false;
extern bool switchView;

void AbstractServer::registerMouseSensitivityHandler(float* pointer) {
    mouseSensitivity = pointer;
}

bool AbstractServer::isOrthoViewSet() {
    return isOrtho;
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
    AbstractDataTree* active = AbstractDataTree::getActiveDataTree();
	for (auto group : elementsBuffer) {
		for (auto type : group.second) {
			active->add(group.first, &type.second);
		}
	}
	elementsBuffer.clear();
	AbstractDataTree::recomputeIntersectionPointsInVisibleTree();

	if (AbstractDataTree::isActiveTreeVisible()) {
        sendStatistics();
	}
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
    sendStaticticsOfGivenTree(AbstractDataTree::getActiveDataTree());
}

void AbstractServer::sendHardResetToSM() {
    char buffer[BUFFER_SIZE];

    sm::CoreToManagerMessage message;
    message.set_messagetype(sm::CoreToManagerMessage_CTMMessageType_HARD_RESET);

    message.SerializeToArray(buffer, BUFFER_SIZE);

    if (sendBytesToSMsocket(buffer, message.GetCachedSize()) < 0) {
        cerr << "Error during sending hard reset to Smeshalist Manager\n";
    }
}

void AbstractServer::sendStatisticsOfCurrentlyVisibleTree() {
    sendStaticticsOfGivenTree(AbstractDataTree::getCurrentlyVisibleDataTree());
}

void AbstractServer::sendStaticticsOfGivenTree(AbstractDataTree* tree) {
    char buffer[BUFFER_SIZE];

    sm::CoreToManagerMessage message;
    message.set_messagetype(sm::CoreToManagerMessage_CTMMessageType_STATISTICS);
    sm::StatisticsInfo info;

    //set elementsCount
    sm::ElementsCount elementsCount;
    tree -> count_visible_elements();
    Statistics stats = tree -> get_statistics();
    map<string, unsigned long> allElements = stats.all_elements_numbers;
    map<string, unsigned long> visibleElements = stats.visible_elements_numbers;

    for(auto& iter : allElements) {
        sm::ElementInfo elementInfo;
        elementInfo.set_total(iter.second);
        elementInfo.set_visible(visibleElements[iter.first]);
        (*elementsCount.mutable_elementinfos())[iter.first] = elementInfo;
    }
    (*info.mutable_elementscount()) = elementsCount;

    info.set_oldestsnapshot(AbstractDataTree::getNumberOfDataTreeInstances()==0 || AbstractDataTree::getVisibleDataTreeIndex()==0);

    //set boundingBox
    sm::BoundingBox boundingBox;
    if (tree -> get_min_x() > tree -> get_max_x()) {  //no data in tree - send zeros
        boundingBox.set_fromx(0);  boundingBox.set_tox(0);
        boundingBox.set_fromy(0);  boundingBox.set_toy(0);
        boundingBox.set_fromz(0);  boundingBox.set_toz(0);
    } else {
        boundingBox.set_fromx(tree -> get_min_x());  boundingBox.set_tox(tree-> get_max_x());
        boundingBox.set_fromy(tree -> get_min_y());  boundingBox.set_toy(tree-> get_max_y());
        boundingBox.set_fromz(tree -> get_min_z());  boundingBox.set_toz(tree-> get_max_z());
    }
    (*info.mutable_boundingbox()) = boundingBox;

    //set GroupInfo
    sm::GroupsInfo groupsInfo;
    vector<int>* groups = tree -> get_all_groupIDs();
    for (int id : *groups) {
        Color c = tree -> get_color_for_group(id);
        sm::Color smColor;
        smColor.set_r(c.r()*255);
        smColor.set_g(c.g()*255);
        smColor.set_b(c.b()*255);
        (*groupsInfo.mutable_allgroups())[id] = smColor;
    }
    (*info.mutable_groupsinfo()) = groupsInfo;

    //set tree name
    info.set_treename(tree->getTreeName());

    (*message.mutable_statisticsinfo()) = info;

    message.SerializeToArray(buffer, BUFFER_SIZE);

    if (sendBytesToSMsocket(buffer, message.GetCachedSize()) < 0) {
        cerr << "Error during sending breakpoint to Smeshalist Manager\n";
    }
}

void AbstractServer::processDataExportMessage(sm::ManagerToCoreMessage* message) {
    string file = message -> objfilepath();
    AbstractDataTree* active = AbstractDataTree::getActiveDataTree();

    active->LOCK();
    exporter.exportToOBJ(active, file);
    active->UNLOCK();
}

void AbstractServer::processDataImportMessage(sm::ManagerToCoreMessage* message) {
    string file = message -> objfilepath();
    AbstractDataTree* active = AbstractDataTree::getActiveDataTree();

    //lock should no to set - it is use during adding elements to data tree
    importer.loadOBJFile(active, file);

    AbstractDataTree::recomputeIntersectionPointsInVisibleTree();
	if (AbstractDataTree::isActiveTreeVisible()) {
        sendStatistics();
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
    AbstractDataTree::recomputeIntersectionPointsInVisibleTree();
    sendStatistics();
}

void AbstractServer::processOptionDataPackage(sm::ManagerToCoreMessage* message) {
    sm::OptionsInfo options = message -> optionsinfo();

    double exponent = options.mousesensitivity();
    *mouseSensitivity = std::pow(BASE, exponent)/BASE;

    setDynamicRendering(options.dynamicrendering());

    showLabels = options.showlabels();

    transparentStructures = options.transparentstructures();

    sm::ColoringType coloringType = options.coloringtype();
    Element::setColoringBuQuality(coloringType == sm::ColoringType::QUALITY_COLORING);

    sm::VisualisationMode mode = options.visualisationmode();
    if (mode == sm::VisualisationMode::MODE_2D && !isOrtho) {
        switchView = true;
        isOrtho = true;
    } else if (mode == sm::VisualisationMode::MODE_3D && isOrtho) {
        switchView = true;
        isOrtho = false;
    }
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
                AbstractDataTree::getActiveDataTree()->createNewInstance();
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_CLEAN:
                if (AbstractDataTree::isActiveTreeVisible()) {  //clean ACTIVE data tree only when it's visible
                    AbstractDataTree::getActiveDataTree()->clean();
                    sendStatistics();
                }
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_NEXT_TREE:
                AbstractDataTree::increaseVisibleDataTreeIndex();
                changeVisibleTree();
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_PREV_TREE:
                AbstractDataTree::decreaseVisibleDataTreeIndex();
                changeVisibleTree();
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_IMPORT:
                processDataImportMessage(&message);
                break;
            case sm::ManagerToCoreMessage_MTCMessageType_EXPORT:
                processDataExportMessage(&message);
                break;
            default:
                cerr << "Unknow message type\n";
                break;
        }
    }
}

void AbstractServer::changeVisibleTree() {
    Statistics statistics = AbstractDataTree::getCurrentlyVisibleDataTree()->get_statistics();
    CoordinatesFilter::getInstance() -> recomputeIntersections(&statistics);
    sendStatisticsOfCurrentlyVisibleTree();
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
                break;
            case structDefinitions::MessageInfo_Type_BREAKPOINT:
                sendBreakpoint();
                break;
            case structDefinitions::MessageInfo_Type_RENDER:
                sendElementsBufferToTree();
                break;
            case structDefinitions::MessageInfo_Type_CLEAN:
                AbstractDataTree::getActiveDataTree()->clean();
                sendStatistics();
                sendAcknowlage();
                break;
            case structDefinitions::MessageInfo_Type_NO_RESET:
                sendAcknowlage();
                break;
            case structDefinitions::MessageInfo_Type_HARD_RESET:
                AbstractDataTree::getCurrentlyVisibleDataTree() -> removeAllSnapshots();
                AbstractDataTree::removeAllFilters();
                AbstractDataTree::getActiveDataTree() -> clean();
                sendHardResetToSM();
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
	delete buffer;
        buffer = new char[(int)header.sizeofdata()];
        nBytes = getBytesFromSocket(buffer, header.sizeofdata());

        if (!package.ParseFromArray(buffer, nBytes)) {
            cerr << "Error during parsing data package\n";
            continue;
        }

        parseVertexSet(&package);
        parseEdgeSet(&package);
        parseTriangleFaceSet(&package);
        parseBlockSet(&package);

        sendAcknowlage();

        delete buffer;
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
