#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>

using namespace std;

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

class Element
{
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

#endif // ELEMENT_H