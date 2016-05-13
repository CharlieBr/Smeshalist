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

    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex3f(coordinates.get_x(), coordinates.get_y(), coordinates.get_z());
    glEnd();
}

void Edge::draw(){
    Point3D v1 = this -> vertexes[0];
    Point3D v2 = this -> vertexes[1];
    cout << "EDGE |" << v1.print_coordinates() << " ----- " << v2.print_coordinates() << "|" <<endl;
}

void Face::draw(){
    cout << "FACE: \n";
    for(unsigned int i = 0; i < this -> edges.size(); i++){
        edges[i].draw();
    }
}

void Block::draw(){
    cout << "BLOCK: \n";
    for(unsigned int i = 0; i < this -> faces.size(); i++){
        faces[i].draw();
    }
}
