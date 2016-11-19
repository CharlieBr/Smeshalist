#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Element.h"

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
        Vertex* clone() {
            Label newLabel(label.get_label_text());
            Vertex* v = new Vertex(vertices.front().clone(), newLabel, quality);
            v -> set_draw_flag(to_draw);
            return v;
        }
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
        Edge* clone() {
            vector<Point3D> newVertices;
            for(auto v : vertices) {
                newVertices.push_back(v.clone());
            }
            Label newLabel(label.get_label_text());
            Edge* e = new Edge(&newVertices, newLabel, quality);
            e -> set_draw_flag(to_draw);
            return e;
        }
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
        Face* clone() {
            vector<Point3D> newVertices;
            for(auto v : vertices) {
                newVertices.push_back(v.clone());
            }
            Label newLabel(label.get_label_text());
            Face* f = new Face(&newVertices, newLabel, quality);
            f -> set_draw_flag(to_draw);
            return f;
        }
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
        Block* clone() {
            vector<Point3D> newVertices;
            for(auto v : vertices) {
                newVertices.push_back(v.clone());
            }
            Label newLabel(label.get_label_text());
            Block* b = new Block(&newVertices, newLabel, quality);
            b -> set_draw_flag(to_draw);
            return b;
        }
};

#endif // STRUCTURES_H
