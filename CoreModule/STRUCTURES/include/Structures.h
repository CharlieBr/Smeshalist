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
    private:
        vector<Face> faces;

    public:
        Block(vector<Point3D> * points, vector<Face> * faces)
            : Element(points, "block"), faces(*faces) {};
        Block(vector<Point3D> * points, vector<Face> * faces, Label label)
            : Element(points, "block", label), faces(*faces) {};

        virtual void draw();
        vector<Face> * getFaces(){ return &faces; }
};

#endif // STRUCTURES_H
