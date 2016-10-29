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
    vector<int> unSelectedGroups;
    vector<int>* allGroupsInTree = dataTree->get_all_groupIDs();

    //create list of all selected groups in SM
    for (auto& filter : filterList) {
        if (filter -> isSelected()) {
            selectedGroups.push_back(filter -> getGroupID());
        } else {
            unSelectedGroups.push_back(filter -> getGroupID());
        }
    }

    //filter
    for (int groupID : *allGroupsInTree) {
        ElementsGroup* elemenGroup = dataTree -> get_group(groupID);

        if(find(unSelectedGroups.begin(), unSelectedGroups.end(), groupID) != unSelectedGroups.end()) {
            elemenGroup -> set_draw_flag(false);
        } else {
            elemenGroup -> set_draw_flag(true);
        }
    }
}
