#include "LinuxDataTree.h"

AbstractDataTree* AbstractDataTree::current = new LinuxDataTree();

void LinuxDataTree::LOCK() {
    mtx.lock();
}

void LinuxDataTree::UNLOCK() {
    mtx.unlock();
}

void LinuxDataTree::createNewInstance() {
    LOCK();
    LinuxDataTree* newInstance = new LinuxDataTree();

    vector<int>* groupIDs = get_all_groupIDs();
    for(auto groupID : *groupIDs) {
        ElementsGroup* group = get_group(groupID);
        vector<string>* types = group ->  get_struct_types();
        for (auto type : *types) {
            ElementsList* elemList = group -> get_list(type);
            ElementsList* clone = elemList->clone();

            newInstance -> add(groupID, clone->get_elements());
        }
    }
    previousInstances.insert(previousInstances.begin(), newInstance);
    UNLOCK();
}
