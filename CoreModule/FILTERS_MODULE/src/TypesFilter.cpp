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
    for (auto& filter : filterList) {
        selectedTypes.push_back(filter -> getTypeName());
    }

    //filter
    for (int groupIdInTree : *allGroupsInTree) {
        ElementsGroup* group = dataTree -> get_group(groupIdInTree);

        if (!group -> is_drawable()) {
            continue;
        }

        vector<string>* types = group -> get_struct_types();

        for (string type : *types) {
            if(find(selectedTypes.begin(), selectedTypes.end(), type) != selectedTypes.end()) {
                group -> get_list(type) -> set_draw_flag(true);
            } else {
                group -> get_list(type) -> set_draw_flag(false);
            }
        }
    }
}
