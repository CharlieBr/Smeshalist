#include "AbstractServer.h"

void AbstractServer::registerStructuresHandler(Data* data) {
    if (this->handler != NULL) {
        this->handler = data;
    }
}

Point3D AbstractServer::parsePoint(const structDefinitions::Point3D* p) {
    return Point3D(p->x(), p->y(), p->z());
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

        Block* block = new Block(&points);
        this -> handler -> add(0, block);
    }
}

void AbstractServer::parseEdgeSet(structDefinitions::EdgeSet* edgeSet) {
    for (int i=0; i<edgeSet->edges_size(); i++) {
        const structDefinitions::Edge e = edgeSet->edges(i);

        vector<Point3D> points;
        points.push_back(parsePoint(&e.v1()));
        points.push_back(parsePoint(&e.v2()));

        Edge* edge = new Edge(&points);
        this -> handler -> add(1, edge);
    }
}

void AbstractServer::parsePoint2DSet(structDefinitions::Point2DSet* pointSet) {
    for (int i=0; i<pointSet->points_size(); i++) {
        const structDefinitions::Point2D p = pointSet->points(i);

        Vertex* v = new Vertex(Point3D(p.x(), p.y(), 0));
        this -> handler -> add(0, v);
    }
}

void AbstractServer::parsePoint3DSet(structDefinitions::Point3DSet* pointSet) {
    for (int i=0; i<pointSet->points_size(); i++) {
        const structDefinitions::Point3D p = pointSet->points(i);

        Vertex* v = new Vertex(parsePoint(&p));
        this -> handler -> add(0, v);
    }
}

void AbstractServer::parseTriangleFaceSet(structDefinitions::TriangleFaceSet* triangleFaceSet) {
    for (int i=0; i<triangleFaceSet->trianglefaces_size(); i++) {
        const structDefinitions::TriangleFace t = triangleFaceSet->trianglefaces(i);

        vector<Point3D> points;

        points.push_back(parsePoint(&t.v1()));
        points.push_back(parsePoint(&t.v2()));
        points.push_back(parsePoint(&t.v3()));

        Face* f = new Face(&points);
        this -> handler -> add(1, f);
    }
}

void AbstractServer::parseVertexSet(structDefinitions::VertexSet* vertexSet) {
    for (int i=0; i<vertexSet->vertexes_size(); i++) {
        const structDefinitions::Vertex v = vertexSet->vertexes(i);

        Vertex* vertex = new Vertex(parsePoint(&v.point()));
        this->handler->add(0, vertex);
    }
}
