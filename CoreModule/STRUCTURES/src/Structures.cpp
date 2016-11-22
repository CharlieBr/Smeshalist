#include "Structures.h"
#include <string.h>

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

void Vertex::draw(Color color){
    Point3D point = this -> vertices.front();

    glColor3f(color.r(), color.g(), color.b());
    glPointSize(4.0f);
    glBegin(GL_POINTS);
        glVertex3f(point.get_x(), point.get_y(), point.get_z());
    glEnd();
/*
    glColor3f(1,0,0);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glRasterPos2f(0,0);
    glPushAttrib(GL_LIST_BIT);                          // Pushes The Display List Bits
    glListBase('a' - 32);                              // Sets The Base Character to 32
    glCallLists(strlen("Perspective"), GL_UNSIGNED_BYTE, "Perspective");    // Draws The Display List Textstrlen(label)
    glPopAttrib();*/
}

void Edge::draw(Color color){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];

    glColor3f(color.r(), color.g(), color.b());
    glBegin(GL_LINES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
    glEnd();
}

void Face::draw(Color color){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];
    Point3D v3 = this -> vertices[2];

    if (!transparentStructures) {
        glColor3f(color.r(), color.g(), color.b());
        glBegin(GL_TRIANGLES);
            glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
            glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
            glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
        glEnd();
    }

    glEnable(GL_POLYGON_OFFSET_LINE);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPolygonOffset(-1,-1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
        glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
}

void Block::draw(Color color){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];
    Point3D v3 = this -> vertices[2];
    Point3D v4 = this -> vertices[3];

    if (!transparentStructures) {
        glColor3f(color.r(), color.g(), color.b());
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

    glEnable(GL_POLYGON_OFFSET_LINE);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPolygonOffset(-1,-1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
}
