#include "Data.h"

UserPreferencesManager* Data::manager = UserPreferencesManager::getInstance();

// ----------------------------
// ------- Data methods -------
// ----------------------------

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
        Color color = group -> get_color();

        if( group -> is_drawable() ){
            group -> draw_elements(color);
        }
    }
}

void Data::add(int group_id, Element* element){
    string element_type = element -> get_type();
    if( !has_group(group_id) ){
        ElementsGroup * group = new ElementsGroup(manager->getGroupColor(group_id));
        groups.insert( pair<int, ElementsGroup*>(group_id, group));
    }
    ElementsGroup* group = groups.at(group_id);
    group -> add(element_type, element);

    //statistics
    statistics.update_elements_counter(element_type, 1);
    if( element -> is_drawable() ){
        if(group -> is_drawable() && group -> get_list(element_type) -> is_drawable()){
            statistics.update_visible_elements_counter(element_type, 1);
        }
    }
    //check coordinates of each point
    //to designate limiting cuboid
    vector<Point3D> vertices = *(element -> get_vertices());
    for(auto &vertex : vertices){
        statistics.update_limiting_cuboid(&vertex);
    }
}

void Data::add(int group_id, vector<Element*>* elements){
    ElementsGroup * group;

    if( !has_group(group_id) ){
        group = new ElementsGroup(manager->getGroupColor(group_id));
        groups.insert( pair<int, ElementsGroup*>(group_id, group));
    }

    if ( elements -> size() > 0 ) {
        string type = elements -> at(0) -> get_type();
        group = groups.at(group_id);
        group -> add(type, elements);
        //statistics
        statistics.update_elements_counter(type, elements -> size());
        long visible_elements_counter = 0;
        for( auto const& element : *(elements)){
            if (element -> is_drawable()){
                visible_elements_counter++;
            }
            //check coordinates of each point
            //to designate limiting cuboid
            vector<Point3D> vertices = *(element -> get_vertices());
            for(auto &vertex : vertices){
                statistics.update_limiting_cuboid(&vertex);
            }
        }
        if(group -> is_drawable() && group -> get_list(type) -> is_drawable()){
            statistics.update_visible_elements_counter(type, visible_elements_counter);
        }
    }
}

void Data::clean(){
    statistics.clean();

    for( auto it : groups ){
        ElementsGroup * group = it.second;
        group -> clean();
        delete group;
    }

    groups.clear();
}

void Data::count_visible_elements(){
    statistics.clean_counters_of_visible_elements();

    for( auto const it : groups) {
        if (it.second -> is_drawable()){
            map<string, unsigned long> result = it.second -> count_visible_elements();

            for( auto const it : result ){
                statistics.update_visible_elements_counter(it.first, it.second);
            }
        }
    }
}

vector<int>* Data::get_all_groupIDs() {
    vector<int>* result = new vector<int>;

    for(map<int,ElementsGroup*>::iterator it = groups.begin(); it != groups.end(); ++it) {
        result -> push_back(it->first);
    }

    return result;
}

Color Data::get_color_for_group(int group_id){
    if(has_group(group_id)){
        return groups.at(group_id) -> get_color();
    }
    return Color(-1.0, -1.0, -1.0);
};

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

void ElementsGroup::draw_elements(Color color){
    for(auto const it : lists){
        ElementsList * elements_list = it.second;

        if( elements_list -> is_drawable() ){
            elements_list -> draw_elements(color);
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

map<string, unsigned long> ElementsGroup::count_visible_elements(){
    map<string, unsigned long> result;

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

ElementsGroup* ElementsGroup::clone() {
    ElementsGroup* result = new ElementsGroup(color);
    result -> set_draw_flag(to_draw);

    vector<string>* types = get_struct_types();

    for (auto type : *types) {
        result -> add(type, get_list(type) -> clone() -> get_elements());
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

void ElementsList::draw_elements(Color color){
    for( unsigned int i = 0; i < elements.size(); i++ ){
        Element * element = elements.at(i);

        if( element -> is_drawable() ){
            element -> draw(color);
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

unsigned long ElementsList::count_visible_elements(){
    long counter = 0;

    for(auto const& it : elements){
        if( it -> is_drawable() ){
            counter += 1;
        }
    }

    return counter;
}

ElementsList* ElementsList::clone() {
    vector<Element*> newElements;
    for (auto element : elements) {
        newElements.push_back(element -> clone());
    }
    ElementsList* result = new ElementsList();
    result -> add(&newElements);
    return result;
}
