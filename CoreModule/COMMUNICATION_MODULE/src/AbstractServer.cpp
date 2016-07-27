#include "AbstractServer.h"

void AbstractServer::registerStructuresHandler(Data* data) {
    if (this->handler != NULL) {
        this->handler = data;
    }
}

void AbstractServer::sendAcknowlage() {
    char buffer[BUFFER_SIZE];

    structDefinitions::MessageInfo ack;
    ack.set_type(structDefinitions::MessageInfo_Type_ACK);

    ack.SerializeToArray(buffer, BUFFER_SIZE);

    if (sendBytesToSocket(buffer, ack.GetCachedSize()) < 0) {
        cerr << "Error during sending ack to client\n";
    }
}

void AbstractServer::sendAccept() {
    char buffer[BUFFER_SIZE];

    structDefinitions::MessageInfo accept;
    accept.set_type(structDefinitions::MessageInfo_Type_ACCEPTED);

    accept.SerializeToArray(buffer, BUFFER_SIZE);

    if (sendBytesToSocket(buffer, accept.GetCachedSize()) < 0) {
        cerr << "Error during sending accept to client\n";
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
                cout << "Breakpoint\n";
                sendAccept();
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
            return;
        }
    }
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
