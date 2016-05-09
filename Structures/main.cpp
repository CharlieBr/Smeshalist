#include <stdio.h>
#include "structures.h"

int main (){
    vector<Point3D> points;
    vector<Point3D>::iterator it;
    it = points.begin();

    Point3D point(1.2, 3.4, 1.4);
    points.insert(it, point);

    Vertex vertex(&points, 1);
    vertex.draw();

    Data::get_instance().add(1, &vertex);
    list<Element*> elements = Data::get_instance().get(1);

    Element * vertex2 = elements.front();
    vertex2 -> draw();


    return 0;
}
