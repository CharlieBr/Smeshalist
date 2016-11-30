#include "Structures.h"

extern bool transparentStructures;

bool Element::colorByQuality = false;

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

    setElementColor(color);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
        glVertex3f(point.get_x(), point.get_y(), point.get_z());
    glEnd();
}

void Edge::draw(Color color){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];

    setElementColor(color);
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
        glEnable(GL_LIGHTING);
        setElementColor(color);
        glBegin(GL_TRIANGLES);
            glNormal3dv(normal);
            glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
            glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
            glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
        glEnd();
        glDisable(GL_LIGHTING);
    }

    glEnable(GL_POLYGON_OFFSET_LINE);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPolygonOffset(-1,-1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);
        glNormal3dv(normal);
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
        glEnable(GL_LIGHTING);
        setElementColor(color);
        glBegin(GL_TRIANGLES);
            glNormal3dv(normals[0]);
            glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
            glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
            glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
        glEnd();

        glBegin(GL_TRIANGLES);
            glNormal3dv(normals[1]);
            glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
            glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
            glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
        glEnd();

        glBegin(GL_TRIANGLES);
            glNormal3dv(normals[2]);
            glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
            glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
            glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
        glEnd();

        glBegin(GL_TRIANGLES);
            glNormal3dv(normals[3]);
            glVertex3f(v4.get_x(), v4.get_y(), v4.get_z());
            glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
            glVertex3f(v3.get_x(), v3.get_y(), v3.get_z());
        glEnd();
        glDisable(GL_LIGHTING);
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
