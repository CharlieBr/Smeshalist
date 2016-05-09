#include "structures.h"
using namespace std;

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
    cout << "POINT (" << coordinates.print_coordinates() << endl;
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


Data& Data::getInstance(){
    static Data instance;
    return instance;
}

map<int, list<Element> > Data::structures;

void Data::add(int key, Element element){
    map<int, list<Element> >::iterator it;
    it = structures.find(key);

    if( it == structures.end() ){
        list<Element> elements_list;
        structures.insert( pair<int, list<Element> >(key, elements_list));
    }

    structures.at(key).push_back(element);
}

list<Element> Data::get(int key){
    return structures.at(key);
}


