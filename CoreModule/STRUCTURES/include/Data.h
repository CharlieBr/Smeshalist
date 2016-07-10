#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>
#include <cfloat>


#include "Element.h"
#include "Statistics.h"

using namespace std;
// -----------------------------------
// --- struct for list of elements ---
// class to perform operations on
// single elements of specified type
// -----------------------------------

class ElementsList {
public:
    vector <Element*> elements;
    bool to_draw = true;

    public:
        bool is_drawable() { return to_draw; }
        void set_draw_flag(bool to_draw) { this -> to_draw = to_draw; }
        void filter_all(bool);
        void draw_elements();

        void add(Element* element) { elements.push_back(element); }
        void add(vector<Element*>*);

        vector<Element*>* get_elements(){ return &elements; }

        //remove all data
        void clean();

        unsigned long count_visible_elements();
};

// -----------------------------------
// --- struct for group o elements ---
// class to perform operations on
// specified types of elements
// -----------------------------------
class ElementsGroup {
    map <string, ElementsList*> lists;
    bool to_draw = true;

    public:
        bool is_drawable() { return to_draw; }
        void set_draw_flag(bool to_draw) { this -> to_draw = to_draw; }
        bool has_list(string);
        void add(string, Element*);
        void add(string, vector<Element*>*);
        void filter_all(bool);
        void draw_elements();
        vector<string>* get_struct_types();
        ElementsList* get_list(string);

        //remove all data
        void clean();

        map<string, unsigned long> count_visible_elements();
};

// --------------------------------
// ----- data root structure ------
// singleton class to perform
// operations on groups of elements
//---------------------------------

class Data {
    static map<int, ElementsGroup*> groups;
    static Statistics statistics;

    Data(){};

    static void check_coordinates(Point3D*);

    public:
        Data(Data const&) = delete;
        void operator=(Data const&) = delete;

        static Data& get_instance();

        static ElementsGroup* get_group(int);
        static bool has_group(int);
        static void filter_all(bool);
        static void draw_elements();

        //returns all available groupIDs (keys)
        static vector<int>* get_all_groupIDs();

        //add single element to proper group and list
        static void add(int, Element*);

        //add list of elements to proper group and list of elements
        static void add(int, vector<Element*>*);

        //remove all data
        static void clean();

        //statistics
        static void count_visible_elements();
        static double get_min_x(){ return statistics.min_x; }
        static double get_max_x(){ return statistics.max_x; }
        static double get_min_y(){ return statistics.min_y; }
        static double get_max_y(){ return statistics.max_y; }
        static double get_min_z(){ return statistics.min_z; }
        static double get_max_z(){ return statistics.max_z; }
        static Statistics get_statistics(){ return statistics; }
};
#endif // DATA_H
