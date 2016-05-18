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
    vector <Element*> elements;
    bool draw;

    public:
        bool is_drawable() { return draw; }
        void set_draw_flag(bool draw) { this -> draw = draw; }
};

// -----------------------------------
// --- struct for group o elements ---
// class to perform operations on
// specified types of elements
// -----------------------------------
class ElementsGroup {
    map <string, ElementsList> groups;
    bool draw;

    public:
        bool is_drawable() { return draw; }
        void set_draw_flag(bool draw) { this -> draw = draw; }

};

// --------------------------------
// ----- data root structure ------
// singleton class to perform
// operations on groups of elements
//---------------------------------

class Data {
    static map<int, list<Element*> > structures;

    private:
        Data(){ };

    public:
        Data(Data const&) = delete;
        void operator=(Data const&) = delete;

        static Data& get_instance();

        void add(int, Element*);

        list<Element*> get(int);

        void draw_elements();
};






#endif // DATA_H
