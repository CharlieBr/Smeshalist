#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>

#include "Element.h"

using namespace std;

// -----------------------------
// ----- data structure --------
// singleton class to perform
// operations on set of elements
//------------------------------

class Data
{
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
