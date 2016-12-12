#ifndef COORDINATESFILTER_H
#define COORDINATESFILTER_H

#include "Data.h"
#include "RelationalOperator.h"
#include "CMathUtils.h"
#include "GL/gl.h"


enum class LogicalConnectiveEnum {AND, OR};


class SingleCoordinateFilter
{
    public:
        SingleCoordinateFilter(double x_coef, double y_coef, double z_coef, double absolute_value, RelationalOperator op) :
            x_coef(x_coef), y_coef(y_coef), z_coef(z_coef), absolute_value(absolute_value), op(op) {}

        bool applyFilter(Element*);
        void draw();
        void recomputeIntersections(Statistics*);
    private:
        double x_coef;
        double y_coef;
        double z_coef;
        double absolute_value;
        RelationalOperator op;
        vector<Point3D*> intersectionPoints;
        static Color cuttingPlaneColor;

        double computeValue(double, double, double);
};

class CoordinatesFilter
{
    public:
        static CoordinatesFilter* getInstance() {
            if (!instance) {
                instance = new CoordinatesFilter();
            }
            return instance;
        }

        void filterTree(Data*);
        void filterElement(Element*);
        void addSimpleCoordinateFilter(SingleCoordinateFilter*);
        void changeLogicalCoonective(LogicalConnectiveEnum);
        void deleteAllFilters() {
            filterList.clear();
        }
        void draw();
        void recomputeIntersections(Statistics*);
    private:
        CoordinatesFilter() {
            logicalConnective = LogicalConnectiveEnum::AND;
        };
        static CoordinatesFilter* instance;
        vector<SingleCoordinateFilter*> filterList;
        LogicalConnectiveEnum logicalConnective;
};

#endif // COORDINATESFILTER_H
