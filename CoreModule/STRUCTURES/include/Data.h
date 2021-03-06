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
#include "Color.h"

#include "UserPreferencesManager.h"

using namespace std;
// -----------------------------------
// --- struct for list of elements ---
// class to perform operations on
// single elements of specified type
// -----------------------------------
class ElementsList {
public:
    vector <Element*> elements;
    bool to_draw = false;

    public:
        bool is_drawable() { return to_draw; }
        void set_draw_flag(bool to_draw) { this -> to_draw = to_draw; }
        void filter_all(bool);
        void draw_elements(Color);

        void add(Element* element) { elements.push_back(element); }
        void add(vector<Element*>*);

        vector<Element*>* get_elements(){ return &elements; }

        ElementsList* clone();

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
    bool to_draw = false;
    Color color;

    public:
        ElementsGroup(Color color) : color(color) {};
        bool is_drawable() { return to_draw; }
        void set_draw_flag(bool to_draw) { this -> to_draw = to_draw; }
        bool has_list(string);
        void add(string, Element*);
        void add(string, vector<Element*>*);
        void filter_all(bool);
        void draw_elements(Color);
        vector<string>* get_struct_types();
        ElementsList* get_list(string);
        Color get_color(){ return color; }

        ElementsGroup* clone();

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
    map<int, ElementsGroup*> groups;

    protected:
        Statistics statistics;
        static UserPreferencesManager* manager;

    public:
        void operator=(Data const&) = delete;

        static Data& get_instance();

        ElementsGroup* get_group(int);
        bool has_group(int);
        void filter_all(bool);
        void draw_elements();

        //returns all available groupIDs (keys)
        vector<int>* get_all_groupIDs();

        //add single element to proper group and list
        virtual void add(int, Element*);

        //add list of elements to proper group and list of elements
        virtual void add(int, vector<Element*>*);

        //remove all data
        void clean();

        //statistics
        void count_visible_elements();
        double get_min_x(){ return statistics.min_x; }
        double get_max_x(){ return statistics.max_x; }
        double get_min_y(){ return statistics.min_y; }
        double get_max_y(){ return statistics.max_y; }
        double get_min_z(){ return statistics.min_z; }
        double get_max_z(){ return statistics.max_z; }
        Statistics get_statistics(){ return statistics; }
        Color get_color_for_group(int);
};
#endif // DATA_H
