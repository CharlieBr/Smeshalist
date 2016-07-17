#include "CoordinatesFilter.h"

CoordinatesFilter* CoordinatesFilter::instance;

bool SingleCoordinateFilter::applyFilter(Element* element) {
    bool result = true;

    vector<Point3D>* vertices = element -> get_vertices();

    for (vector<Point3D>::iterator it = vertices->begin() ; it != vertices->end() && result; ++it) {
        double value = computeValue(it -> get_x(), it -> get_y(), it -> get_z());

        switch(op) {
            case RelationalOperator::lt: result = absolute_value > value; break;
            case RelationalOperator::le: result = absolute_value >=value; break;
            case RelationalOperator::ge: result = absolute_value <=value; break;
            case RelationalOperator::gt: result = absolute_value < value; break;
            default: result = true;
        }
    }

    return result;
}

double SingleCoordinateFilter::computeValue(double x, double y, double z) {
    return x*x_coef + y*y_coef + z*z_coef;
}

void CoordinatesFilter::addSimpleCoordinateFilter(SingleCoordinateFilter* filter) {
    filterList.push_back(filter);
}

void CoordinatesFilter::changeLogicalCoonective(LogicalConnectiveEnum lc) {
    logicalConnective = lc;
}

void CoordinatesFilter::filterElement(Element* element) {
    if (!element -> is_drawable()) {
        return;
    }

    bool any = false;   //use for OR operator
    bool all = true;    //use for AND operator
    bool result;

    for (vector<SingleCoordinateFilter*>::iterator filter = filterList.begin() ; filter != filterList.end(); ++filter) {
        result = (*filter) -> applyFilter(element);
        all = all && result;
        any = any || result;
    }

    if (logicalConnective == LogicalConnectiveEnum::AND) {
        element->set_draw_flag(all);
    } else {
        element->set_draw_flag(any);
    }
}


void CoordinatesFilter::filterTree(Data* dataTree) {
    vector<int>* groupIDs = dataTree -> get_all_groupIDs();

    for (vector<int>::iterator groupsIter = groupIDs->begin() ; groupsIter != groupIDs->end(); ++groupsIter) {
        ElementsGroup* elementsGroup = dataTree -> get_group(*groupsIter);

        //ommit groups which are not draw
        if (!elementsGroup -> is_drawable()) {
            continue;
        }

        vector<string>* typeIDs = elementsGroup -> get_struct_types();

        for (vector<string>::iterator typeIter = typeIDs->begin() ; typeIter != typeIDs->end(); ++typeIter) {
            ElementsList* elementsList = elementsGroup -> get_list(*typeIter);

            //ommit lists which are not draw
            if (!elementsList -> is_drawable()) {
                continue;
            }

            vector<Element*>* elements = elementsList -> get_elements();

            for (vector<Element*>::iterator elem = elements->begin() ; elem != elements->end(); ++elem) {
                filterElement(*elem);
            }
        }
    }
}
