#include "QualityFilter.h"

QualityFilter* QualityFilter::instance;
vector<SingleQualityFilter*> QualityFilter::filterList;

void QualityFilter::addSingleFilter(SingleQualityFilter* filter) {
    filterList.push_back(filter);
}

void QualityFilter::deleteAllFilters() {
    filterList.clear();
}

void QualityFilter::filterTree(Data* dataTree) {
    vector<int>* groupIDs = dataTree -> get_all_groupIDs();

    for (vector<int>::iterator groupsIter = groupIDs->begin() ; groupsIter != groupIDs->end(); ++groupsIter) {
        ElementsGroup* elementsGroup = dataTree -> get_group(*groupsIter);

        //ommit groups which are not draw
        if (!elementsGroup->is_drawable()) {
            continue;
        }

        vector<string>* typeIDs = elementsGroup -> get_struct_types();
        for (vector<string>::iterator typeIter = typeIDs->begin() ; typeIter != typeIDs->end(); ++typeIter) {
            ElementsList* elementsList = elementsGroup -> get_list(*typeIter);

            //ommit lists which are not draw
            if (!elementsGroup->is_drawable()) {
                continue;
            }

            vector<Element*>* elements = elementsList -> get_elements();
            for (vector<Element*>::iterator elem = elements->begin() ; elem != elements->end(); ++elem) {
                bool result = false;

                for (vector<SingleQualityFilter*>::iterator filter = filterList.begin() ; !result && filter != filterList.end(); ++filter) {
                    result = (*filter) -> applyFilter(*elem);
                }

                (*elem)->set_draw_flag(result);
            }
        }
    }
}

bool SingleQualityFilter::applyFilter(Element* element) {
    //TODO after quality field willbe added to Element class
    //int quality = element -> get_quality();
    double quality = 0;
    bool result = false;

    if (!leftValue) {
        switch (leftOp) {
            case RelationalOperator::lt : result = leftValue->getValue() < quality; break;
            case RelationalOperator::le : result = leftValue->getValue() <=quality; break;
            case RelationalOperator::eq : result = leftValue->getValue() ==quality; break;
            default : result = true;
        }
    }

    if (result && !rightValue) {
        switch (rightOp) {
            case RelationalOperator::lt : result = quality < rightValue->getValue(); break;
            case RelationalOperator::le : result = quality <=rightValue->getValue(); break;
            case RelationalOperator::eq : result = quality ==rightValue->getValue(); break;
            default : result = true;
        }
    }

    //TODO change it!!!!!
    result = true;
    return result;
}
