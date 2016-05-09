#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>

using namespace std;

// --- points -----
class Point3D {
    double x;
    double y;
    double z;

    public:
        Point3D(double x, double y, double z) : x(x), y(y), z(z) {};
        double get_x() { return x; }
        double get_y() { return y; }
        double get_z() { return z; }

        string print_coordinates();
};

class Label {
    string text;

    public:
        Label(){};
        Label(string text) : text(text) {};
        string get_label_text(){ return text; }
        void set_label_text(string text){ this -> text = text; }
};

// ------------------------------------------
// ------------- mesh elements --------------
// ------------------------------------------
class Element { //kind of interface for mesh elements
    protected:
        vector<Point3D> vertexes;
        string type;
        int groupID;
        Label label;

    public:
        Element(vector<Point3D> * points, string type, int groupID, Label label)
            : vertexes(*points), type(type), groupID(groupID), label(label) {};
        Element(vector<Point3D> * points, string type, int groupID)
            : vertexes(*points), type(type), groupID(groupID) {};

        virtual void draw(){};
        vector<Point3D> * get_vertexes() { return &vertexes; }
        string get_type(){ return type; }
        void set_label(Label label){ this -> label = label; }
        Label get_label(){ return label; }
 };

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


// -----------------------------
// ----- data structure --------
// singleton class to perform
// operations on set of elements
//------------------------------

class Data {
    static map<int, list<Element*> > structures;

    private:
        Data(){ };

    public:
        Data(Data const&) = delete;
        void operator=(Data const&) = delete;

        static Data& get_instance();

        void add(int, Element*);

        list<Element*> get(int);

        void draw_elements(int);
};

#endif
