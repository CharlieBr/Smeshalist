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
    if ( has_group(group_id) ){
        return groups.at(group_id);
    } else {
        return NULL;
    }
}

bool Data::has_group(int group_id){
    map<int, ElementsGroup* >::iterator it;
    it = groups.find(group_id);

    if ( it == groups.end() ){
        return false;
    }

    return true;
}

void Data::filter_all(bool to_draw){
    for( auto const it : groups ){
        ElementsGroup * group = it.second;
        group -> set_draw_flag(to_draw);
        group -> filter_all(to_draw);
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

void Data::add(int group_id, vector<Element*>* elements){
    ElementsGroup * group;

    if( !has_group(group_id) ){
        group = new ElementsGroup;
        groups.insert( pair<int, ElementsGroup*>(group_id, group));
    }

    if ( elements -> size() > 0 ) {
        string type = elements -> at(0) -> get_type();
        group = groups.at(group_id);
        group -> add(type, elements);
    }
}

vector<int>* Data::get_all_groups() {
    vector<int>* result = new vector<int>;

    for(map<int,ElementsGroup*>::iterator it = groups.begin(); it != groups.end(); ++it) {
        result -> push_back(it->first);
    }

    return result;
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

void ElementsGroup::add(string elements_type, vector<Element*>* elements){
    ElementsList * elements_list;

    if( !has_list(elements_type) ){
        elements_list = new ElementsList;
        lists.insert( pair<string, ElementsList*>(elements_type, elements_list) );
    }

    if( elements -> size() > 0 ){
        elements_list = lists.at(elements_type);
        elements_list -> add(elements);
    }
}


void ElementsGroup::filter_all(bool to_draw ){
    for( auto const& it : lists){
        ElementsList * elements_list = it.second;
        elements_list -> set_draw_flag(to_draw);
        elements_list -> filter_all(to_draw);
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

ElementsList* ElementsGroup::get_list(string elements_type){
    if( has_list(elements_type) ){
        return lists.at(elements_type);
    } else {
        return NULL;
    }
}


// -------------------------------
// ---- ElementsList methods -----
// -------------------------------
void ElementsList::add(vector<Element*> *new_elements){
    vector<Element*>::iterator it;
    it = elements.end();

    elements.insert( it, new_elements -> begin(), new_elements -> end() );
}

void ElementsList::filter_all(bool to_draw){
    for( unsigned int i = 0; i < elements.size(); i++){
        Element * element = elements.at(i);
        element -> set_draw_flag(to_draw);
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

