#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Element.h"
#include <GL/glut.h>


class Vertex : public Element {
    public:
        Vertex(vector<Point3D> * points, int groupID)
            : Element(points, "point", groupID) {};
        Vertex(vector<Point3D> * points, int groupID, Label label)
            : Element(points, "point", groupID, label) {};
        virtual void draw();
};

class Edge : public Element {
    public:
        Edge(vector<Point3D> * points, int groupID)
            : Element(points, "edge", groupID) {};
        Edge(vector<Point3D> * points, int groupID, Label label)
            : Element(points, "edge", groupID, label) {};
        virtual void draw();
};

class Face : public Element {
    private:
        vector<Edge> edges;

    public:
        Face(vector<Point3D> * points, int groupID, vector<Edge> * edges)
            : Element(points, "face", groupID), edges(*edges) {};
        Face(vector<Point3D> * points, int groupID, vector<Edge> * edges, Label label)
            : Element(points, "face", groupID, label), edges(*edges) {};
        virtual void draw();
        vector<Edge> * getEdges(){ return &edges; }
};

class Block : public Element {
    private:
        vector<Face> faces;

    public:
        Block(vector<Point3D> * points, int groupID, vector<Face> * faces)
            : Element(points, "block", groupID), faces(*faces) {};
        Block(vector<Point3D> * points, int groupID, vector<Face> * faces, Label label)
            : Element(points, "block", groupID, label), faces(*faces) {};

        virtual void draw();
        vector<Face> * getFaces(){ return &faces; }
};

#endif // STRUCTURES_H
