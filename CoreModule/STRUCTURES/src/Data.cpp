#include "Data.h"

// ----------------------------
// ------- Data methods -------
// ----------------------------
map<int, ElementsGroup* > Data::groups;

Data& Data::get_instance(){
    static Data instance;
    return instance;
}

ElementsGroup* Data::get_group(int group_id){
    return groups.at(group_id);
}

bool Data::has_group(int group_id){
    map<int, ElementsGroup* >::iterator it;
    it = groups.find(group_id);

    if ( it == groups.end() ){
        return false;
    }

    return true;
}

void Data::filter_all(){
    for( auto const it : groups ){
        ElementsGroup * group = it.second;
        group -> set_draw_flag(true);
        group -> filter_all();
    }
}

void Data::draw_elements(){
    for( auto const it : groups ){
        ElementsGroup * group = it.second;

        if( group -> is_drawable() ){
            group -> draw_elements();
        }
    }
}

void Data::add(int group_id, Element* element){
    if( !has_group(group_id) ){
        ElementsGroup * group = new ElementsGroup;
        groups.insert( pair<int, ElementsGroup*>(group_id, group));
    }

    string element_type = element -> get_type();
    ElementsGroup* group = groups.at(group_id);
    group -> add(element_type, element);
}

void Data::add_group(int group_id, ElementsGroup* group){
    if( has_group(group_id) ){
        cout << "Cannot add group. The group with id " << group_id <<" already exists!\n";
        return;
    }

    map<int, ElementsGroup*>::iterator it = groups.end();
    groups.insert(it, pair<int, ElementsGroup*>(group_id, group));
    return;
}

// --------------------------------------
// ------- ElementsGroup methods --------
// --------------------------------------
bool ElementsGroup::has_list(string elements_type){
    map<string,ElementsList*>::iterator it;
    it = lists.find(elements_type);

    if( it == lists.end() ){
        return false;
    }

    return true;
}

void ElementsGroup::add(string elements_type, Element* element){
    if( !has_list(elements_type) ){
        ElementsList * element_list = new ElementsList;
        lists.insert( pair<string, ElementsList* >(elements_type, element_list));
    }

    ElementsList * elements_list = lists.at(elements_type);
    elements_list -> add(element);
}

void ElementsGroup::filter_all(){
    for( auto const& it : lists){
        ElementsList * elements_list = it.second;
        elements_list -> set_draw_flag(true);
    }
}

void ElementsGroup::draw_elements(){
    for(auto const it : lists){
        ElementsList * elements_list = it.second;

        if( elements_list -> is_drawable() ){
            elements_list -> draw_elements();
        }
    }
}


// -------------------------------
// ---- ElementsList methods -----
// -------------------------------
void ElementsList::filter_all(){
    for( unsigned int i = 0; i < elements.size(); i++){
        Element * element = elements.at(i);
        element -> set_draw_flag(true);
    }
}

void ElementsList::draw_elements(){
    for( unsigned int i = 0; i < elements.size(); i++ ){
        Element * element = elements.at(i);

        if( element -> is_drawable() ){
            element -> draw();
        }
    }
}

