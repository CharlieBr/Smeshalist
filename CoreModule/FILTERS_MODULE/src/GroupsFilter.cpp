#include "GroupsFilter.h"

vector<SingleGroupFilter*> GroupsFilter::filterList;
GroupsFilter* GroupsFilter::instance;

void GroupsFilter::addSimpleGroupFilter(SingleGroupFilter* filter) {
    filterList.push_back(filter);
}

void GroupsFilter::deleteAllFilters() {
    filterList.clear();
}

void GroupsFilter::filterTree(Data* dataTree) {
    vector<int> selectedGroups;
    vector<int>* allGroupsInTree = dataTree->get_all_groupIDs();

    //create list of all selected groups in SM
    for (vector<SingleGroupFilter*>::iterator it = filterList.begin() ; it != filterList.end(); ++it) {
        selectedGroups.push_back((*it) -> getGroupID());
    }

    //filter
    for (vector<int>::iterator it = allGroupsInTree -> begin() ; it != allGroupsInTree -> end(); ++it) {
        ElementsGroup* elemenGroup = dataTree -> get_group(*it);

        if(find(selectedGroups.begin(), selectedGroups.end(), *it) != selectedGroups.end()) {
            elemenGroup -> set_draw_flag(true);
        } else {
            elemenGroup -> set_draw_flag(false);
        }
    }


}
