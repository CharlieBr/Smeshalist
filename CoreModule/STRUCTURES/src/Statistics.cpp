#include "Statistics.h"
using namespace std;

Statistics::Statistics(){
    all_elements_numbers = [] {
        map<string, unsigned long> result;

        result["all"] = 0;
        result["vertex"] = 0;
        result["edge"] = 0;
        result["face"] = 0;
        result["block"] = 0;

        return result;
    }();

    visible_elements_numbers = all_elements_numbers;

    min_x = DBL_MAX;
    min_y = DBL_MAX;
    min_z = DBL_MAX;
    max_x = -DBL_MAX;
    max_y = -DBL_MAX;
    max_z = -DBL_MAX;
}

void Statistics::clean(){
    all_elements_numbers["all"] = 0;
    all_elements_numbers["vertex"] = 0;
    all_elements_numbers["edge"] = 0;
    all_elements_numbers["face"] = 0;
    all_elements_numbers["block"] = 0;
    visible_elements_numbers["all"] = 0;
    visible_elements_numbers["vertex"] = 0;
    visible_elements_numbers["edge"] = 0;
    visible_elements_numbers["face"] = 0;
    visible_elements_numbers["block"] = 0;
    min_x = DBL_MAX;
    min_y = DBL_MAX;
    min_z = DBL_MAX;
    max_x = -DBL_MAX;
    max_y = -DBL_MAX;
    max_z = -DBL_MAX;
    return;
}

void Statistics::update_limiting_cuboid(Point3D* point){
    double x = point -> get_x();
    double y = point -> get_y();
    double z = point -> get_z();

    if( x < min_x ){
        min_x = x;
    }

    if( x > max_x ){
        max_x = x;
    }

    if( y < min_y ){
        min_y = y;
    }

    if ( y > max_y ){
        max_y = y;
    }

    if( z < min_z ){
        min_z = z;
    }

    if ( z > max_z ){
        max_z = z;
    }

    return;
}

void Statistics::update_elements_counter(string type, int amount){
    all_elements_numbers["all"] += amount;
    all_elements_numbers[type] += amount;
}

void Statistics::update_visible_elements_counter(string type, int amount){
    visible_elements_numbers["all"] += amount;
    visible_elements_numbers[type] += amount;
}

void Statistics::clean_counters_of_visible_elements(){
    visible_elements_numbers["all"] = 0;
    visible_elements_numbers["vertex"] = 0;
    visible_elements_numbers["edge"] = 0;
    visible_elements_numbers["face"] = 0;
    visible_elements_numbers["block"] = 0;
}
