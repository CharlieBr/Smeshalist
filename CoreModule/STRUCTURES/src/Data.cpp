#include "Data.h"

// ----------------------------
// ------- Data methods -------
// ----------------------------
map<int, ElementsGroup* > Data::groups;
map<string, int> Data::all_elements_numbers = [] {
    map<string, int> result;

    result["all"] = 0;
    result["vertex"] = 0;
    result["edge"] = 0;
    result["face"] = 0;
    result["block"] = 0;

    return result;
}();

map<string, int> Data::visible_elements_numbers = Data::all_elements_numbers;

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
    string element_type = element -> get_type();
    all_elements_numbers["all"] += 1;
    all_elements_numbers[element_type] += 1;

    if( element -> is_drawable() ){
        visible_elements_numbers["all"] += 1;
        visible_elements_numbers[element_type] += 1;
    }

    if( !has_group(group_id) ){
        ElementsGroup * group = new ElementsGroup;
        groups.insert( pair<int, ElementsGroup*>(group_id, group));
    }


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
        all_elements_numbers["all"] += elements -> size();
        all_elements_numbers[type] += elements -> size();

        //assumed that all elements have the same to_draw flag
        if( elements -> at(0) -> is_drawable() ){
            visible_elements_numbers["all"] += elements -> size();
            visible_elements_numbers[type] += elements -> size();
        }

        group = groups.at(group_id);
        group -> add(type, elements);
    }
}


void Data::clean(){
    all_elements_numbers["all"] = 0;
    all_elements_numbers["vertex"] = 0;
    all_elements_numbers["edge"] = 0;
    all_elements_numbers["face"] = 0;
    all_elements_numbers["block"] = 0;

    for( auto it : groups ){
        ElementsGroup * group = it.second;
        group -> clean();
        delete group;
    }

    groups.clear();
}

long Data::get_elements_number(string type){
    map<string, int>::iterator it;
    it = all_elements_numbers.find(type);

    if( it == all_elements_numbers.end() ){
        return 0;
    } else {
        return all_elements_numbers[type];
    }
}

void Data::count_visible_elements(){
    visible_elements_numbers["all"] = 0;
    visible_elements_numbers["vertex"] = 0;
    visible_elements_numbers["edge"] = 0;
    visible_elements_numbers["face"] = 0;
    visible_elements_numbers["block"] = 0;

    for( auto const it : groups) {
        map<string, int> result = it.second -> count_visible_elements();

        for( auto const it : result ){
            visible_elements_numbers["all"] += it.second;
            visible_elements_numbers[ it.first ] += it.second;
        }
    }
}

long Data::get_visible_elements_number(string type){
    map<string, int>::iterator it;
    it = visible_elements_numbers.find(type);
    if( it == visible_elements_numbers.end() ){
        return 0;
    } else {
        return visible_elements_numbers[type];
    }
}

vector<int>* Data::get_all_groupIDs() {
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

void ElementsGroup::clean(){
    for (auto& it : lists){
        ElementsList * elements_list = it.second;
        elements_list -> clean();
        delete elements_list;
    }

    lists.clear();
}

map<string, int> ElementsGroup::count_visible_elements(){
    map<string, int> result;

    for(auto const& it : lists){
        ElementsList* elements_list = it.second;

        if( elements_list -> is_drawable() ){
            string type = it.first;
            result[type] = elements_list -> count_visible_elements();
        }
    }

    return result;
}

vector<string>* ElementsGroup::get_struct_types() {
    vector<string>* result = new vector<string>;

    for(map<string,ElementsList*>::iterator it = lists.begin(); it != lists.end(); ++it) {
        result -> push_back(it->first);
    }

    return result;
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

void ElementsList::clean(){
    for( auto& it: elements ){
        Element * element = it;
        delete element;
    }

    elements.clear();
}

long ElementsList::count_visible_elements(){
    long counter = 0;

    for(auto const& it : elements){
        if( it -> is_drawable() ){
            counter += 1;
        }
    }

    return counter;
}
