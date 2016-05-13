#include "Data.h"

map<int, list<Element*> > Data::structures;

Data& Data::get_instance(){
    static Data instance;
    return instance;
}

list<Element*> Data::get(int key){
    return structures.at(key);
}

void Data::add(int key, Element* element){
    map<int, list<Element*> >::iterator it;
    it = structures.find(key);

    if( it == structures.end() ){
        list<Element*> elements_list;
        structures.insert( pair<int, list<Element*> >(key, elements_list));
    }

    structures.at(key).push_back(element);
}

void Data::draw_elements(){
    for (map<int, list<Element*>>::iterator it = structures.begin(); it != structures.end(); it++) {
        for (Element* e : get(it->first)) {
            e->draw();
        }
    }
}
