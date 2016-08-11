#include "CoordinatesFilter.h"

CoordinatesFilter* CoordinatesFilter::instance;

bool SingleCoordinateFilter::applyFilter(Element* element) {
    bool result = true;

    vector<Point3D>* vertices = element -> get_vertices();

    for (Point3D& vertex : *vertices) {
        double value = computeValue(vertex.get_x(), vertex.get_y(), vertex.get_z());

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

    for (auto& filter : filterList) {
        result = filter -> applyFilter(element);
        all &= result;
        any |= result;
    }

    if (logicalConnective == LogicalConnectiveEnum::AND) {
        element->set_draw_flag(all);
    } else {
        element->set_draw_flag(any);
    }
}


void CoordinatesFilter::filterTree(Data* dataTree) {
    vector<int>* groupIDs = dataTree -> get_all_groupIDs();

    for (int groupID : *groupIDs) {
        ElementsGroup* elementsGroup = dataTree -> get_group(groupID);

        //ommit groups which are not draw
        if (!elementsGroup -> is_drawable()) {
            continue;
        }

        vector<string>* typeIDs = elementsGroup -> get_struct_types();

        for(string typeID : *typeIDs) {
            ElementsList* elementsList = elementsGroup -> get_list(typeID);

            //ommit lists which are not draw
            if (!elementsList -> is_drawable()) {
                continue;
            }

            vector<Element*>* elements = elementsList -> get_elements();

            for(Element* element : *elements) {
                filterElement(element);
            }
        }
    }
}
