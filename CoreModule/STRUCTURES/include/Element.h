#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>

using namespace std;

// ------------------------------------------
// - basic structure to represent 3d points -
// ------------------------------------------
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

// -------------------------------------------
// ------ element additional attribute -------
// -------------------------------------------
class Label {
    string text;

    public:
        Label(){};
        Label(string text) : text(text) {};
        string get_label_text(){ return text; }
        void set_label_text(string text){ this -> text = text; }
};

// -------------------------------------------
// - kind of interface for mesh elements -----
// -------------------------------------------
class Element
{
    protected:
        vector<Point3D> vertices;
        string type;
        Label label;
        bool to_draw;

    public:
        Element(vector<Point3D> * points, string type, Label label)
            : vertices(*points), type(type), label(label) {};
        Element(vector<Point3D> * points, string type)
            : vertices(*points), type(type) {};
        //constructors for Vertex
        Element(Point3D point, string type, Label label)
            : type(type), label(label) { vertices.insert(vertices.begin(), point); };
        Element(Point3D point, string type)
            : type(type) { vertices.insert(vertices.begin(), point); };


        virtual void draw(){};
        vector<Point3D> * get_vertices() { return &vertices; }
        string get_type(){ return type; }
        void set_label(Label label){ this -> label = label; }
        Label get_label(){ return label; }
        bool is_drawable(){ return to_draw; }
        void set_draw_flag(bool to_draw) { this -> to_draw = to_draw; }
};

#endif // ELEMENT_H
