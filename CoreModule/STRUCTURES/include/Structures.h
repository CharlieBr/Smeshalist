#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Element.h"
#include <GL/glut.h>

// -----------------------------------------------
// ----------- mesh elements ---------------------
// -----------------------------------------------

class Vertex : public Element {
    public:
        Vertex(Point3D point)
            : Element(point, "vertex") {};
        Vertex(Point3D point, Label label)
            : Element(point, "vertex", label) {};
        Vertex(Point3D point, double quality)
            : Element(point, "vertex", quality) {};
        Vertex(Point3D point, Label label, double quality)
            : Element(point, "vertex", label, quality) {};
        virtual void draw(Color);
};

class Edge : public Element {
    public:
        Edge(vector<Point3D> * points)
            : Element(points, "edge") {};
        Edge(vector<Point3D> * points, Label label)
            : Element(points, "edge", label) {};
        Edge(vector<Point3D> * points, double quality)
            : Element(points, "edge", quality) {};
        Edge(vector<Point3D> * points, Label label, double quality)
            : Element(points, "edge", label, quality) {};
        virtual void draw(Color);
};

class Face : public Element {
    public:
        Face(vector<Point3D> * points)
            : Element(points, "face"){};
        Face(vector<Point3D> * points, Label label)
            : Element(points, "face", label) {};
        Face(vector<Point3D> * points, double quality)
            : Element(points, "face", quality){};
        Face(vector<Point3D> * points, Label label, double quality)
            : Element(points, "face", label, quality) {};

        virtual void draw(Color);
};

class Block : public Element {
    public:
        Block(vector<Point3D> * points)
            : Element(points, "block") {};
        Block(vector<Point3D> * points, Label label)
            : Element(points, "block", label) {};
        Block(vector<Point3D> * points, double quality)
            : Element(points, "block", quality) {};
        Block(vector<Point3D> * points, Label label, double quality)
            : Element(points, "block", label, quality) {};

        virtual void draw(Color);
};

#endif // STRUCTURES_H
