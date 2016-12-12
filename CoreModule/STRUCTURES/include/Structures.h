#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Element.h"

//CMATHUTILS
class Utils {
    public:

    static double* getVectorProduct(double* a, double* b) {
        double* result = new double[3];
        result[0] = a[1]*b[2] - a[2]*b[1];
        result[1] = -(a[0]*b[2] - a[2]*b[0]);
        result[2] = a[0]*b[1] - a[1]*b[0];
        return result;
    }

    static double* getNormal(Point3D* a, Point3D* b, Point3D* c) {
        int x=0;
        int y=1;
        int z=2;

        double ab[3] = {b->get_x()-a->get_x(), b->get_y()-a->get_y(), b->get_z()-a->get_z()};
        double ac[3] = {c->get_x()-a->get_x(), c->get_y()-a->get_y(), c->get_z()-a->get_z()};

        double* product = getVectorProduct(ab, ac);
        double len = std::sqrt(product[x]*product[x] + product[y]*product[y] + product[z]*product[z]);

        if (len == 0) {
            double* result = new double[3]{0, 0, 0};
            return result;
        }

        product[x] /= len;
        product[y] /= len;
        product[z] /= len;

        return product;
    }
};

extern bool transparentStructures;

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
        double* normal;
        Face(vector<Point3D> * points)
            : Element(points, "face"){ normal = Utils::getNormal(&vertices[0], &vertices[1], &vertices[2]); };
        Face(vector<Point3D> * points, Label label)
            : Element(points, "face", label) { normal = Utils::getNormal(&vertices[0], &vertices[1], &vertices[2]); };
        Face(vector<Point3D> * points, double quality)
            : Element(points, "face", quality){ normal = Utils::getNormal(&vertices[0], &vertices[1], &vertices[2]); };
        Face(vector<Point3D> * points, Label label, double quality)
            : Element(points, "face", label, quality) { normal = Utils::getNormal(&vertices[0], &vertices[1], &vertices[2]); };

        virtual void draw(Color);
        Face* clone() {
            vector<Point3D> newVertices;
            for(auto v : vertices) {
                newVertices.push_back(v.clone());
            }
            Label newLabel(label.get_label_text());
            Face* f = new Face(&newVertices, newLabel, quality);
            f -> set_draw_flag(to_draw);
            f -> normal = normal;
            return f;
        }
};

class Block : public Element {
    public:
        vector<double*> normals;
        Block(vector<Point3D> * points)
            : Element(points, "block") {computeNormals();};
        Block(vector<Point3D> * points, Label label)
            : Element(points, "block", label) {computeNormals();};
        Block(vector<Point3D> * points, double quality)
            : Element(points, "block", quality) {computeNormals();};
        Block(vector<Point3D> * points, Label label, double quality)
            : Element(points, "block", label, quality) {computeNormals();};

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
        void computeNormals() {
            Point3D v1 = this -> vertices[0];
            Point3D v2 = this -> vertices[1];
            Point3D v3 = this -> vertices[2];
            Point3D v4 = this -> vertices[3];

            normals.push_back(Utils::getNormal(&v1, &v2, &v3));
            normals.push_back(Utils::getNormal(&v1, &v2, &v4));
            normals.push_back(Utils::getNormal(&v1, &v4, &v3));
            normals.push_back(Utils::getNormal(&v4, &v2, &v3));
        }
};

#endif // STRUCTURES_H
