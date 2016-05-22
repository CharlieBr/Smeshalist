#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>

#include "Element.h"

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
        void add(Element* element) { elements.push_back(element); }
        void draw_elements();
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
        void filter_all();
        void draw_elements();
};

// --------------------------------
// ----- data root structure ------
// singleton class to perform
// operations on groups of elements
//---------------------------------

class Data {
    static map<int, ElementsGroup*> groups;

    private:
        Data(){};

    public:
        Data(Data const&) = delete;
        void operator=(Data const&) = delete;

        static Data& get_instance();

        ElementsGroup* get_group(int);
        bool has_group(int);
        void add(int, Element*);
        void filter_all();
        void draw_elements();
};






#endif // DATA_H
