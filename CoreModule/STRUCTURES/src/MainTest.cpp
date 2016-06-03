#include<iostream>
#include<typeinfo>
#include <assert.h>
#include "Structures.h"
#include "Data.h"
using namespace std;

int main(void){
    Point3D point(1.2, 3.4, 3.4);
    Vertex vertex(point);

    Point3D point2(1.0, 3.0, 3.9);
    Vertex vertex2(point2);

    Point3D point3(1.0, 3.0, 3.9);
    Vertex vertex3(point3);

    vector<Point3D> points;
    points.push_back(point);
    points.push_back(point2);
    Edge edge(&points);

    Data * data = &(Data::get_instance());

    data -> add(2, &vertex);
    data -> add(2, &vertex2);
    data -> add(2, &vertex3);
    data -> add(2, &edge);

    ElementsGroup * group2 = data -> get_group(2);
    assert( group2 != NULL );

    ElementsList * vertex_list = group2 -> get_list("vertex");
    assert( vertex_list != NULL );

    ElementsList * edge_list1 = group2 -> get_list("edge");
    assert( edge_list1 != NULL );

    vector<Element*> * vertices = vertex_list -> get_elements();
    assert( vertices -> size() == 3 );

    vector<Element*> * edges = edge_list1 -> get_elements();
    assert( edges -> size() == 1 );


    vector<Point3D> edge1_points;
    edge1_points.push_back(Point3D(4.5, 4.2, 8.9));
    edge1_points.push_back(Point3D(2.3, 4.1, -1.0));
    Edge edge1(&edge1_points);

    vector<Point3D> edge2_points;
    edge2_points.push_back(Point3D(1.5, 8.2, -8.9));
    edge2_points.push_back(Point3D(4.3, 2.1, 1.0));
    Edge edge2(&edge2_points);

    vector<Element*> elements;
    elements.push_back(&edge1);
    elements.push_back(&edge2);

    data -> add(1, &elements);

    ElementsGroup * group1 = data -> get_group(1);
    assert( group1 != NULL );

    ElementsList * edge_list2 = group1 -> get_list("edge");
    assert( edge_list2 != NULL );

    vector<Element*> * edges2 = edge_list2 -> get_elements();
    assert( edges2 -> size() == 2 );

    data -> filter_all(false);
    for(unsigned int i = 0; i < vertices -> size(); i++){
        Element * element = vertices -> at(i);
        assert( element -> is_drawable() == false );
    }

    for(unsigned int i = 0; i < edges -> size(); i++){
        Element * element = edges -> at(i);
        assert( element -> is_drawable() == false );
    }

    for(unsigned int i = 0; i < edges2 -> size(); i++){
        Element * element = edges2 -> at(i);
        assert( element -> is_drawable() == false );
    }

    data -> filter_all(true);
    for(unsigned int i = 0; i < vertices -> size(); i++){
        Element * element = vertices -> at(i);
        assert( element -> is_drawable() == true );
    }

    for(unsigned int i = 0; i < edges -> size(); i++){
        Element * element = edges -> at(i);
        assert( element -> is_drawable() == true );
    }

    for(unsigned int i = 0; i < edges2 -> size(); i++){
        Element * element = edges2 -> at(i);
        assert( element -> is_drawable() == true );
    }

    data -> draw_elements();

    return 0;
}
