#include "AbstractDataTree.h"

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
        CoordinatesFilter::getInstance() -> recomputeIntersections(&statistics);
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
