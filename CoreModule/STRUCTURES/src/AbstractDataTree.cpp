#include "AbstractDataTree.h"

vector<AbstractDataTree*> AbstractDataTree::previousInstances;
bool AbstractDataTree::readyToBeCleaned = false;
int AbstractDataTree::visibleDataTreeIndex=-1; //-1-current; >=0 - previous

AbstractDataTree* AbstractDataTree::getActiveDataTree() {
    return active;
}

void AbstractDataTree::draw_elements() {
    (*this.*drawFunction)();
}

void AbstractDataTree::drawElements() {
    Data::draw_elements();
}

void AbstractDataTree::drawNothing() {
    readyToBeCleaned = true;
}

void AbstractDataTree::clean() {
    LOCK();
    drawFunction = &AbstractDataTree::drawNothing;
    while (!readyToBeCleaned) {
        sleepThread(10);
    }
    Data::clean();
    recomputeIntersectionPoints();
    drawFunction = &AbstractDataTree::drawElements;
    readyToBeCleaned = false;
    UNLOCK();
}

void AbstractDataTree::add(int groupID, Element* element) {
    LOCK();
    QualityFilter::getInstance() -> filterElement(element);
    CoordinatesFilter::getInstance() -> filterElement(element);
    Data::add(groupID, element);
    GroupsFilter::getInstance() -> filterTree(this);
    TypesFilter::getInstance() -> filterTree(this);
    UNLOCK();
}

void AbstractDataTree::add(int groupID, vector<Element*>* elements) {
    LOCK();
    for(auto const& element : *elements){
        QualityFilter::getInstance() -> filterElement(element);
        CoordinatesFilter::getInstance() -> filterElement(element);
    }
    Data::add(groupID, elements);
    GroupsFilter::getInstance() -> filterTree(this);
    TypesFilter::getInstance() -> filterTree(this);
    UNLOCK();
}

void AbstractDataTree::reloadFlitersInAllTrees(vector<SingleGroupFilter*> *groupFilters, vector<SingleTypesFilter*> *typesFilters,
    vector<SingleCoordinateFilter*> *coordinateFilters, LogicalConnectiveEnum* conjuntion, vector<SingleQualityFilter*> *qualityFilters) {
    active -> reloadFliters(groupFilters, typesFilters, coordinateFilters, conjuntion, qualityFilters);

    //filters are already reloaded, previous instances should only be filtered, even without setting locks (this trees are immutable)
    for (auto tree : previousInstances) {
        tree -> filterDataTree();
    }
}

void AbstractDataTree::reloadFliters(vector<SingleGroupFilter*> *groupFilters, vector<SingleTypesFilter*> *typesFilters,
    vector<SingleCoordinateFilter*> *coordinateFilters, LogicalConnectiveEnum* conjuntion, vector<SingleQualityFilter*> *qualityFilters) {

    LOCK();

    if (groupFilters != NULL) {
        GroupsFilter::getInstance() -> deleteAllFilters();
        for(auto const& groupFilter : *groupFilters){
            GroupsFilter::getInstance() -> addSimpleGroupFilter(groupFilter);
        }
    }

    if (typesFilters != NULL) {
        TypesFilter::getInstance() -> deleteAllFilters();
        for(auto const& typesFilter : *typesFilters){
            TypesFilter::getInstance() -> addSingleFilter(typesFilter);
        }
    }

    if (coordinateFilters != NULL) {
        CoordinatesFilter::getInstance() -> deleteAllFilters();
        for(auto const& coordinateFilter : *coordinateFilters){
            CoordinatesFilter::getInstance() -> addSimpleCoordinateFilter(coordinateFilter);
        }
    }

    if (conjuntion != NULL) {
        CoordinatesFilter::getInstance() -> changeLogicalCoonective(*conjuntion);
    }

    if (qualityFilters != NULL) {
        QualityFilter::getInstance() -> deleteAllFilters();
        for(auto const& qualityFilter : *qualityFilters){
            QualityFilter::getInstance() -> addSingleFilter(qualityFilter);
        }
    }

    filterDataTree();

    UNLOCK();
}

void AbstractDataTree::filterDataTree() {
    GroupsFilter::getInstance() -> filterTree(this);
    TypesFilter::getInstance() -> filterTree(this);
    QualityFilter::getInstance() -> filterTree(this);
    CoordinatesFilter::getInstance() -> filterTree(this);
}

void AbstractDataTree::recomputeIntersectionPointsInVisibleTree() {
    getCurrentlyVisibleDataTree() -> recomputeIntersectionPoints();
}

void AbstractDataTree::recomputeIntersectionPoints() {
    CoordinatesFilter::getInstance() -> recomputeIntersections(&statistics);
}

AbstractDataTree* AbstractDataTree::getDataTreeInstance(int index) {
    if (previousInstances.size() == 0 || index == -1) {
        return active;
    }

    return previousInstances[index];
}

AbstractDataTree* AbstractDataTree::getCurrentlyVisibleDataTree() {
    return getDataTreeInstance(visibleDataTreeIndex);
}

int AbstractDataTree::getNumberOfDataTreeInstances() {
    return AbstractDataTree::previousInstances.size();
}

int AbstractDataTree::getVisibleDataTreeIndex() {
    return visibleDataTreeIndex;
}

void AbstractDataTree::decreaseVisibleDataTreeIndex() {
    visibleDataTreeIndex--;
    if (visibleDataTreeIndex < -1) {
        visibleDataTreeIndex = getNumberOfDataTreeInstances()-1;
    }
}

void AbstractDataTree::increaseVisibleDataTreeIndex() {
    visibleDataTreeIndex++;
    if (visibleDataTreeIndex >= getNumberOfDataTreeInstances()) {
        visibleDataTreeIndex = -1;
    }
}

bool AbstractDataTree::isActiveTreeVisible() {
    return visibleDataTreeIndex == -1;
}

void AbstractDataTree::cloneDataTreeToNewInstance(AbstractDataTree* newInstance) {
	vector<int>* groupIDs = get_all_groupIDs();
	for (auto groupID : *groupIDs) {
		ElementsGroup* group = get_group(groupID);
		vector<string>* types = group->get_struct_types();
		for (auto type : *types) {
			ElementsList* elemList = group->get_list(type);
			ElementsList* clone = elemList->clone();

			newInstance->add(groupID, clone->get_elements());
		}
	}
	previousInstances.insert(previousInstances.begin(), newInstance);
}

string AbstractDataTree::getTreeName() {
    return treeName;
}
