#include "AbstractDataTree.h"

void AbstractDataTree::add(int groupID, Element* element) {
    LOCK();
    QualityFilter::getInstance() -> filterElement(element);
    CoordinatesFilter::getInstance() -> filterElement(element);
    Data::add(groupID, element);
    UNLOCK();
}

void AbstractDataTree::add(int groupID, vector<Element*>* elements) {
    LOCK();
    for(auto const& element : *elements){
        QualityFilter::getInstance() -> filterElement(element);
        CoordinatesFilter::getInstance() -> filterElement(element);
    }
    Data::add(groupID, elements);
    UNLOCK();
}

void AbstractDataTree::reloadFliters(vector<SingleGroupFilter*> groupFilters, vector<SingleTypesFilter*> typesFilters, vector<SingleCoordinateFilter*> coordinateFilters,
    vector<SingleQualityFilter*> qualityFilters) {

    LOCK();
    GroupsFilter::getInstance() -> deleteAllFilters();
    TypesFilter::getInstance() -> deleteAllFilters();
    CoordinatesFilter::getInstance() -> deleteAllFilters();
    QualityFilter::getInstance() -> deleteAllFilters();


    for(auto const& groupFilter : groupFilters){
        GroupsFilter::getInstance() -> addSimpleGroupFilter(groupFilter);
    }
    for(auto const& typesFilter : typesFilters){
        TypesFilter::getInstance() -> addSingleFilter(typesFilter);
    }
    for(auto const& coordinateFilter : coordinateFilters){
        CoordinatesFilter::getInstance() -> addSimpleCoordinateFilter(coordinateFilter);
    }
    for(auto const& qualityFilter : qualityFilters){
        QualityFilter::getInstance() -> addSingleFilter(qualityFilter);
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
