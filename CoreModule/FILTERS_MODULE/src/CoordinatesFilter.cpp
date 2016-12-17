#include "CoordinatesFilter.h"

CoordinatesFilter* CoordinatesFilter::instance;
Color SingleCoordinateFilter::cuttingPlaneColor = UserPreferencesManager::getInstance() -> getCuttingPlaneColor();

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

        if  (!result) {
            break;
        }
    }

    return result;
}

double SingleCoordinateFilter::computeValue(double x, double y, double z) {
    return x*x_coef + y*y_coef + z*z_coef;
}

void SingleCoordinateFilter::draw() {
    glColor4f(cuttingPlaneColor.r(), cuttingPlaneColor.g(), cuttingPlaneColor.b(), cuttingPlaneColor.a());
    glBegin(GL_POLYGON);
    for (Point3D* point : intersectionPoints) {
        glVertex3d(point->get_x(), point->get_y(), point->get_z());
    }
    glEnd();
}

void SingleCoordinateFilter::recomputeIntersections(Statistics* stats) {
    intersectionPoints.clear();

    //compute for x
    if (x_coef != 0) {
        double x = (absolute_value - y_coef*stats->min_y - z_coef*stats->min_z)/x_coef;
        if (stats->min_x <= x && x <= stats->max_x) {
            intersectionPoints.push_back(new Point3D(x, stats->min_y, stats->min_z));
        }

        x = (absolute_value - y_coef*stats->min_y - z_coef*stats->max_z)/x_coef;
        if (stats->min_x <= x && x <= stats->max_x) {
            intersectionPoints.push_back(new Point3D(x, stats->min_y, stats->max_z));
        }

        x = (absolute_value - y_coef*stats->max_y - z_coef*stats->min_z)/x_coef;
        if (stats->min_x <= x && x <= stats->max_x) {
            intersectionPoints.push_back(new Point3D(x, stats->max_y, stats->min_z));
        }

        x = (absolute_value - y_coef*stats->max_y - z_coef*stats->max_z)/x_coef;
        if (stats->min_x <= x && x <= stats->max_x) {
            intersectionPoints.push_back(new Point3D(x, stats->max_y, stats->max_z));
        }
    }

    //compute for y
    if (y_coef != 0) {
        double y = (absolute_value - x_coef*stats->min_x - z_coef*stats->min_z)/y_coef;
        if (stats->min_y <= y && y <= stats->max_y) {
            intersectionPoints.push_back(new Point3D(stats->min_x, y, stats->min_z));
        }

        y = (absolute_value - x_coef*stats->max_x - z_coef*stats->min_z)/y_coef;
        if (stats->min_y <= y && y <= stats->max_y) {
            intersectionPoints.push_back(new Point3D(stats->max_x, y, stats->min_z));
        }

        y = (absolute_value - x_coef*stats->min_x - z_coef*stats->max_z)/y_coef;
        if (stats->min_y <= y && y <= stats->max_y) {
            intersectionPoints.push_back(new Point3D(stats->min_x, y, stats->max_z));
        }

        y = (absolute_value - x_coef*stats->max_x - z_coef*stats->max_z)/y_coef;
        if (stats->min_y <= y && y <= stats->max_y) {
            intersectionPoints.push_back(new Point3D(stats->max_x, y, stats->max_z));
        }
    }

    //compute for z
    if (z_coef != 0) {
        double z = (absolute_value - x_coef*stats->min_x - y_coef*stats->min_y)/z_coef;
        if (stats->min_z <= z && z <= stats->max_z) {
            intersectionPoints.push_back(new Point3D(stats->min_x, stats->min_y, z));
        }

        z = (absolute_value - x_coef*stats->max_x - y_coef*stats->min_y)/z_coef;
        if (stats->min_z <= z && z <= stats->max_z) {
            intersectionPoints.push_back(new Point3D(stats->max_x, stats->min_y, z));
        }

        z = (absolute_value - x_coef*stats->min_x - y_coef*stats->max_y)/z_coef;
        if (stats->min_z <= z && z <= stats->max_z) {
            intersectionPoints.push_back(new Point3D(stats->min_x, stats->max_y, z));
        }

        z = (absolute_value - x_coef*stats->max_x - y_coef*stats->max_y)/z_coef;
        if (stats->min_z <= z && z <= stats->max_z) {
            intersectionPoints.push_back(new Point3D(stats->max_x, stats->max_y, z));
        }
    }

    intersectionPoints = CMathUtils::sortPoints(intersectionPoints);
}

void CoordinatesFilter::recomputeIntersections(Statistics* stats) {
    for (auto& filter : filterList) {
        filter -> recomputeIntersections(stats);
    }
}

void CoordinatesFilter::draw() {
    for (auto& filter : filterList) {
        filter -> draw();
    }
}

void CoordinatesFilter::addSimpleCoordinateFilter(SingleCoordinateFilter* filter) {
    filterList.push_back(filter);
}

void CoordinatesFilter::changeLogicalCoonective(LogicalConnectiveEnum lc) {
    logicalConnective = lc;
}

void CoordinatesFilter::filterElement(Element* element) {
    if (!element -> has_proper_quality()) {
        element->set_draw_flag(false);
        return;
    }

    if (filterList.size()==0) {
        element->set_draw_flag(true);
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
