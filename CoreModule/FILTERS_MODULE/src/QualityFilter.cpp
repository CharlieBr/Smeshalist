#include "QualityFilter.h"

QualityFilter* QualityFilter::instance;
vector<SingleQualityFilter*> QualityFilter::filterList;

void QualityFilter::addSingleFilter(SingleQualityFilter* filter) {
    filterList.push_back(filter);
}

void QualityFilter::deleteAllFilters() {
    filterList.clear();
}

void QualityFilter::filterElement(Element* element) {
    bool result = false;

    for (auto& filter : filterList) {
        result |= filter -> applyFilter(element);
    }
    if (filterList.size() == 0) {
        result = true;
    }

    element->set_has_proper_quality_flag(result);
}

void QualityFilter::filterTree(Data* dataTree) {
    vector<int>* groupIDs = dataTree -> get_all_groupIDs();

    for (int groupID : *groupIDs) {
        ElementsGroup* elementsGroup = dataTree -> get_group(groupID);

        //ommit groups which are not draw
        if (!elementsGroup->is_drawable()) {
            continue;
        }

        vector<string>* typeIDs = elementsGroup -> get_struct_types();

        for (string typeID : *typeIDs) {
            ElementsList* elementsList = elementsGroup -> get_list(typeID);

            //ommit lists which are not draw
            if (!elementsGroup->is_drawable()) {
                continue;
            }

            vector<Element*>* elements = elementsList -> get_elements();
            for (Element* element : *elements) {
                filterElement(element);
            }
        }
    }
}

bool SingleQualityFilter::applyFilter(Element* element) {
    double quality = element->get_quality();
    bool result = true;

    if (leftValue != NULL) {
        switch (leftOp) {
            case RelationalOperator::lt : result = leftValue->getValue() < quality; break;
            case RelationalOperator::le : result = leftValue->getValue() <=quality; break;
            case RelationalOperator::eq : result = leftValue->getValue() ==quality; break;
            default : result = true;
        }
    }

    if (result && rightValue != NULL) {
        switch (rightOp) {
            case RelationalOperator::lt : result = quality < rightValue->getValue(); break;
            case RelationalOperator::le : result = quality <=rightValue->getValue(); break;
            case RelationalOperator::eq : result = quality ==rightValue->getValue(); break;
            default : result = true;
        }
    }
    return result;
}
