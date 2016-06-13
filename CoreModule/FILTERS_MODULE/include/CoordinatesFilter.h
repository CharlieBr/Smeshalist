#ifndef COORDINATESFILTER_H
#define COORDINATESFILTER_H

#include "../../STRUCTURES/include/Data.h"
#include "RelationalOperator.h"


enum class LogicalConnectiveEnum {AND, OR};


class SingleCoordinateFilter
{
    public:
        SingleCoordinateFilter(double x_coef, double y_coef, double z_coef, double absolute_value, RelationalOperator op) :
            x_coef(x_coef), y_coef(y_coef), z_coef(z_coef), absolute_value(absolute_value), op(op) {}

        bool applyFilter(Element*);

    private:
        double x_coef;
        double y_coef;
        double z_coef;
        double absolute_value;
        RelationalOperator op;

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
        void addSimpleCoordinateFilter(SingleCoordinateFilter*);
        void changeLogicalCoonective(LogicalConnectiveEnum);
        void deleteAllFilters() {
            filterList.clear();
        }
    private:
        CoordinatesFilter() {
            logicalConnective = LogicalConnectiveEnum::AND;
        };
        static CoordinatesFilter* instance;
        vector<SingleCoordinateFilter*> filterList;
        LogicalConnectiveEnum logicalConnective;
};

#endif // COORDINATESFILTER_H
