#ifndef QUALITYFILTER_H
#define QUALITYFILTER_H

#include "../../STRUCTURES/include/Data.h"
#include "RelationalOperator.h"

class Double
{
    public:
        Double(double value) : value(value) {};
        double getValue() {
            return value;
        }
    private:
        double value;
};

class SingleQualityFilter
{
    public:
        SingleQualityFilter(Double* leftValue, RelationalOperator leftOp, RelationalOperator rightOp, Double* rightValue):
            leftValue(leftValue), rightValue(rightValue), leftOp(leftOp), rightOp(rightOp) {};
        bool applyFilter(Element*);
    private:
        Double* leftValue;
        Double* rightValue;
        RelationalOperator leftOp;
        RelationalOperator rightOp;
};

class QualityFilter
{
    public:
        static QualityFilter* getInstance() {
            if (!instance) {
                instance = new QualityFilter();
            }
            return instance;
        }
        void addSingleFilter(SingleQualityFilter*);
        void deleteAllFilters();
        void filterTree(Data*);
    protected:
    private:
        static QualityFilter* instance;
        static vector<SingleQualityFilter*> filterList;
};

#endif // QUALITYFILTER_H
