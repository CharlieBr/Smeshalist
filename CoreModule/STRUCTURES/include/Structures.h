#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Element.h"
//#include <GL/glut.h>


class Vertex : public Element {
    public:
        Vertex(Point3D point)
            : Element(point, "point") {};
        Vertex(Point3D point, Label label)
            : Element(point, "point", label) {};
        virtual void draw();
};

class Edge : public Element {
    public:
        Edge(vector<Point3D> * points)
            : Element(points, "edge") {};
        Edge(vector<Point3D> * points, Label label)
            : Element(points, "edge", label) {};
        virtual void draw();
};

class Face : public Element {
    public:
        Face(vector<Point3D> * points)
            : Element(points, "face"){};
        Face(vector<Point3D> * points, Label label)
            : Element(points, "face", label) {};

        virtual void draw();
};

class Block : public Element {
    public:
        Block(vector<Point3D> * points)
            : Element(points, "block") {};
        Block(vector<Point3D> * points, Label label)
            : Element(points, "block", label) {};

        virtual void draw();
};

#endif // STRUCTURES_H
