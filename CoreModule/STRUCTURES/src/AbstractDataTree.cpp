#include "AbstractDataTree.h"

AbstractDataTree& AbstractDataTree::getInstance(){
    static AbstractDataTree instance;
    return instance;
}

void AbstractDataTree::add(int groupID, Element* element) {
    Data::add(groupID, element);
}

void AbstractDataTree::add(int groupID, vector<Element*>* elements) {
    Data::add(groupID, elements);
}
