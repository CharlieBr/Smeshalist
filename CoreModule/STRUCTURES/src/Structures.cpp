#include "Structures.h"

// ----------------------------
// -------- points ------------
// ----------------------------

string Point3D::print_coordinates(){
    char coordinates[25];
    sprintf(coordinates, "(%.3f, %.3f, %.3f)", x, y, z);
    return coordinates;
}


// --------------------------------------
// ------- mesh elements methods --------
// --------------------------------------

void Vertex::draw(){
    Point3D point = this -> vertices.front();

    glPointSize(2);
    glBegin(GL_POINTS);
        glVertex3f(point.get_x(), point.get_y(), point.get_z());
    glEnd();
}

void Edge::draw(){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];

    glBegin(GL_LINES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
    glEnd();
}

void Face::draw(){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];
    Point3D v3 = this -> vertices[2];

    glBegin(GL_TRIANGLES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();
}

void Block::draw(){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];
    Point3D v3 = this -> vertices[2];
    Point3D v4 = this -> vertices[3];

    glBegin(GL_TRIANGLES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();
}
