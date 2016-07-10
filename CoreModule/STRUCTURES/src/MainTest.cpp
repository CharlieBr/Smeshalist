#include<iostream>
#include<typeinfo>
#include <assert.h>
#include "Structures.h"
#include "Data.h"
using namespace std;

struct test_struct{
    string name = "Kasia";
};

int main(void){
    Point3D point(1.2, 3.4, 3.4);
    Vertex * vertex = new Vertex(point, 1.2);

    Point3D point2(1.0, 3.0, 3.9);
    Vertex * vertex2 = new Vertex(point2);

    Point3D point3(-1.0, 3.0, 4.9);
    Vertex * vertex3 = new Vertex(point3);

    vector<Point3D> points;
    points.push_back(point);
    points.push_back(point2);
    Edge * edge = new Edge(&points);

    Data * data = &(Data::get_instance());

    vertex -> set_quality(1.0);
    assert( vertex -> get_quality() == 1.0 );
    assert( vertex2 -> get_quality() == 0.0 );

    data -> add(2, vertex);

    assert( data -> get_min_x() == 1.2 );
    assert( data -> get_max_x() == 1.2 );
    assert( data -> get_min_y() == 3.4 );
    assert( data -> get_max_y() == 3.4 );
    assert( data -> get_min_z() == 3.4 );
    assert( data -> get_max_z() == 3.4 );

    data -> add(2, vertex2);

    assert( data -> get_min_x() == 1.0 );
    assert( data -> get_max_x() == 1.2 );
    assert( data -> get_min_y() == 3.0 );
    assert( data -> get_max_y() == 3.4 );
    assert( data -> get_min_z() == 3.4 );
    assert( data -> get_max_z() == 3.9 );

    data -> add(2, vertex3);
    data -> add(2, edge);

    assert( data -> get_min_x() == -1.0 );
    assert( data -> get_max_x() == 1.2 );
    assert( data -> get_min_y() == 3.0 );
    assert( data -> get_max_y() == 3.4 );
    assert( data -> get_min_z() == 3.4 );
    assert( data -> get_max_z() == 4.9 );


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
    Edge * edge1 = new Edge(&edge1_points);

    vector<Point3D> edge2_points;
    edge2_points.push_back(Point3D(1.5, 8.2, -8.9));
    edge2_points.push_back(Point3D(4.3, 2.1, 1.0));
    Edge * edge2 = new Edge(&edge2_points);

    vector<Element*> elements;
    elements.push_back(edge1);
    elements.push_back(edge2);

    data -> add(1, &elements);

    assert( data -> get_min_x() == -1.0 );
    assert( data -> get_max_x() == 4.5 );
    assert( data -> get_min_y() == 2.1 );
    assert( data -> get_max_y() == 8.2 );
    assert( data -> get_min_z() == -8.9 );
    assert( data -> get_max_z() == 8.9 );


    ElementsGroup * group1 = data -> get_group(1);
    assert( group1 != NULL );

    ElementsList * edge_list2 = group1 -> get_list("edge");
    assert( edge_list2 != NULL );

    vector<Element*> * edges2 = edge_list2 -> get_elements();
    assert( edges2 -> size() == 2 );

    Statistics statistics = data -> get_statistics();

    assert( statistics.all_elements_numbers["all"] == 6 );
    assert( statistics.all_elements_numbers["vertex"] == 3 );
    assert( statistics.all_elements_numbers["edge"] == 3 );

    assert( statistics.visible_elements_numbers["all"] == 6 );
    assert( statistics.visible_elements_numbers["vertex"] == 3 );
    assert( statistics.visible_elements_numbers["edge"] == 3 );


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

    data -> count_visible_elements();

    statistics = data -> get_statistics();
    assert( statistics.visible_elements_numbers["all"] == 0 );
    assert( statistics.visible_elements_numbers["vertex"] == 0 );
    assert( statistics.visible_elements_numbers["edge"]== 0 );

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

    data -> count_visible_elements();
    statistics = data -> get_statistics();
    assert( statistics.visible_elements_numbers["all"] == 6 );
    assert( statistics.visible_elements_numbers["vertex"] == 3 );
    assert( statistics.visible_elements_numbers["edge"] == 3 );

    //cleaning
    data -> draw_elements();
    data -> clean();

    vertex = nullptr;
    vertex2 = nullptr;
    vertex3 = nullptr;
    edge = nullptr;
    edge1 = nullptr;
    edge2 = nullptr;
    group1 = nullptr;
    group2 = nullptr;
    vertices = nullptr;
    edges = nullptr;
    edges2 = nullptr;

    assert( data -> has_group(2) == false );
    assert( data -> has_group(1) == false );
    statistics = data -> get_statistics();
    assert( statistics.all_elements_numbers["all"] == 0 );
    assert( statistics.all_elements_numbers["vertex"] == 0 );
    assert( statistics.all_elements_numbers["edge"] == 0 );
    assert( statistics.visible_elements_numbers["all"] == 0 );
    assert( statistics.visible_elements_numbers["vertex"] == 0 );
    assert( statistics.visible_elements_numbers["edge"]== 0 );

    assert( data -> get_min_x() == DBL_MAX );
    assert( data -> get_max_x() == DBL_MIN );
    assert( data -> get_min_y() == DBL_MAX );
    assert( data -> get_max_y() == DBL_MIN );
    assert( data -> get_min_z() == DBL_MAX );
    assert( data -> get_max_z() == DBL_MIN );

    return 0;
}
