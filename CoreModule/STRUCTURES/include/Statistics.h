#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>
#include <cfloat>

#include "Element.h"
using namespace std;

class Statistics {
    public:
        //coordinates of limiting cuboid
        double min_x;
        double max_x;
        double min_y;
        double max_y;
        double min_z;
        double max_z;

        map<string, unsigned long> all_elements_numbers;
        map<string, unsigned long> visible_elements_numbers;

        Statistics();

        void clean();
        void update_limiting_cuboid(Point3D*);
        void update_elements_counter(string, int);
        void update_visible_elements_counter(string, int);
        void clean_counters_of_visible_elements();
};

#endif // STATISTICS_H_H

