#ifndef ABSTRACTDATATREE_H
#define ABSTRACTDATATREE_H

#include "Data.h"
#include "GroupsFilter.h"
#include "CoordinatesFilter.h"
#include "TypesFilter.h"
#include "QualityFilter.h"


class AbstractDataTree : public Data
{
    public:
        void add(int, Element*);
        void add(int, vector<Element*>*);
        void reloadFliters(vector<SingleGroupFilter*>*, vector<SingleTypesFilter*>*, vector<SingleCoordinateFilter*>*, LogicalConnectiveEnum*, vector<SingleQualityFilter*>*);
    protected:
        virtual void LOCK()=0;
        virtual void UNLOCK()=0;
        void filterDataTree();
    private:

};

#endif // ABSTRACTDATATREE_H
