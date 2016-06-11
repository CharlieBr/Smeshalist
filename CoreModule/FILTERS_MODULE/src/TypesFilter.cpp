#include "TypesFilter.h"

vector<SingleTypesFilter*> TypesFilter::filterList;
TypesFilter* TypesFilter::instance;


void TypesFilter::addSingleFilter(SingleTypesFilter* filter) {
    filterList.push_back(filter);
}

void TypesFilter::deleteAllFilters() {
    filterList.clear();
}

void TypesFilter::filterTree(Data* dataTree) {
    vector<int>* allGroupsInTree = dataTree->get_all_groupIDs();
    vector<string> selectedTypes;

    //create list of all selected types in SM
    for (vector<SingleTypesFilter*>::iterator it = filterList.begin() ; it != filterList.end(); ++it) {
        selectedTypes.push_back((*it) -> getTypeName());
    }

    //filter
    for (vector<int>::iterator groupIter = allGroupsInTree -> begin() ; groupIter != allGroupsInTree -> end(); ++groupIter) {
        //ommite groups which are not drawable
        ElementsGroup* group = dataTree -> get_group(*groupIter);
        if (!group -> is_drawable()) {
            continue;
        }

        vector<string>* types = group -> get_struct_types();
        for (vector<string>::iterator typesIter = types -> begin() ; typesIter != types -> end(); ++typesIter) {
            if(find(selectedTypes.begin(), selectedTypes.end(), *typesIter) != selectedTypes.end()) {
                group -> get_list(*typesIter) -> set_draw_flag(true);
            } else {
                group -> get_list(*typesIter) -> set_draw_flag(false);
            }
        }
    }
}
