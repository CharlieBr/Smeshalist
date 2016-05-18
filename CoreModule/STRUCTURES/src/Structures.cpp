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
    Point3D coordinates = this -> vertexes.front();
    //cout << "POINT " << coordinates.print_coordinates() << endl;
    //cout << "POINT (" << coordinates.print_coordinates() << endl;

    glPointSize(2);
    glBegin(GL_POINTS);
        glVertex3f(coordinates.get_x(), coordinates.get_y(), coordinates.get_z());
    glEnd();
}

void Edge::draw(){
    Point3D v1 = this -> vertexes[0];
    Point3D v2 = this -> vertexes[1];
    //cout << "EDGE |" << v1.print_coordinates() << " ----- " << v2.print_coordinates() << "|" <<endl;

    glBegin(GL_LINES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
    glEnd();
}

void Face::draw(){
    Point3D v1 = this -> vertexes[0];
    Point3D v2 = this -> vertexes[1];
    Point3D v3 = this -> vertexes[2];

    glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.1f, 0.0f);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glColor3f(0.1f, 0.0f, 0.1f);
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glColor3f(0.0f, 0.1f, 0.1f);
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();
}

void Block::draw(){
    Point3D v1 = this -> vertexes[0];
    Point3D v2 = this -> vertexes[1];
    Point3D v3 = this -> vertexes[2];
    Point3D v4 = this -> vertexes[3];

    glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.1f, 0.0f);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glColor3f(0.1f, 0.0f, 0.1f);
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glColor3f(0.0f, 0.1f, 0.1f);
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.1f, 0.0f);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glColor3f(0.1f, 0.0f, 0.1f);
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.1f, 0.0f);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
        glColor3f(0.0f, 0.1f, 0.1f);
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
        glColor3f(0.1f, 0.0f, 0.1f);
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glColor3f(0.0f, 0.1f, 0.1f);
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();
}
