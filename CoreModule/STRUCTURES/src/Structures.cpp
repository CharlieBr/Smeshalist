#include "Structures.h"

extern bool transparentStructures;
extern bool showLabels;
bool Element::colorByQuality = false;
float pointSize = UserPreferencesManager::getInstance()->getPointSize();

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
    glPointSize(pointSize);
    glBegin(GL_POINTS);
        glVertex3f(point.get_x(), point.get_y(), point.get_z());
    glEnd();

    if(showLabels){
        glColor3f(color.r(), color.g(), color.b());
        glRasterPos3d(point.get_x(), point.get_y() + 0.01, point.get_z());
        print::printStringFont10(this -> label.get_label_text().c_str());
    }
}

void Edge::draw(Color color){
    Point3D v1 = this -> vertices[0];
    Point3D v2 = this -> vertices[1];

    setElementColor(color);
    glBegin(GL_LINES);
        glVertex3f(v1.get_x(), v1.get_y(), v1.get_z());
        glVertex3f(v2.get_x(), v2.get_y(), v2.get_z());
    glEnd();

    if(showLabels){
        double center_x = (v1.get_x() + v2.get_x())/2;
        double center_y = (v1.get_y() + v2.get_y())/2;
        double center_z = (v1.get_z() + v2.get_z())/2;
        glColor3f(color.r(), color.g(), color.b());
        glRasterPos3d(center_x, center_y + 0.001, center_z);
        print::printStringFont10(this -> label.get_label_text().c_str());
    }
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

        //set color of edges
        glColor3f(0.0f, 0.0f, 0.0f);
    } else {
        setElementColor(color);
    }

    glEnable(GL_POLYGON_OFFSET_LINE);
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

    if(showLabels){
        double max_y = v1.get_y();
        unsigned int max_idx = 0;
        for(unsigned int i = 1; i < this -> vertices.size(); i++){
            if(this -> vertices[i].get_y() > max_y){
                max_y = this -> vertices[i].get_y();
                max_idx = i;
            }
        }
        glColor3f(color.r(), color.g(), color.b());
        glRasterPos3d(vertices[max_idx].get_x(), vertices[max_idx].get_y() + 0.001, vertices[max_idx].get_z());
        print::printStringFont10(this -> label.get_label_text().c_str());
    }
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

        //set color of edges
        glColor3f(0.0f, 0.0f, 0.0f);
    } else {
        setElementColor(color);
    }

    glEnable(GL_POLYGON_OFFSET_LINE);
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

    if(showLabels){
        double max_y = v1.get_y();
        unsigned int max_idx = 0;
        for(unsigned int i = 1; i < this -> vertices.size(); i++){
            if(this -> vertices[i].get_y() > max_y){
                max_y = this -> vertices[i].get_y();
                max_idx = i;
            }
        }
        glColor3f(color.r(), color.g(), color.b());
        glRasterPos3d(vertices[max_idx].get_x(), vertices[max_idx].get_y() + 0.001, vertices[max_idx].get_z());
        print::printStringFont10(this -> label.get_label_text().c_str());
    }
}
