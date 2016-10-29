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
        static void recomputeIntersectionPointsInVisibleTree(int);
        static void reloadFlitersInAllTrees(vector<SingleGroupFilter*>*, vector<SingleTypesFilter*>*, vector<SingleCoordinateFilter*>*, LogicalConnectiveEnum*, vector<SingleQualityFilter*>*);
        static int getNumberOfDataTreeInstances();
        virtual void createNewInstance() = 0;
        static AbstractDataTree* getDataTreeInstance(int);
        static AbstractDataTree* getCurrent();
        void draw_elements();
        void clean();
    protected:
        virtual void LOCK()=0;
        virtual void UNLOCK()=0;
        void (AbstractDataTree::*drawFunction)();
        void filterDataTree();
        void recomputeIntersectionPoints();
        void reloadFliters(vector<SingleGroupFilter*>*, vector<SingleTypesFilter*>*, vector<SingleCoordinateFilter*>*, LogicalConnectiveEnum*, vector<SingleQualityFilter*>*);
        static vector<AbstractDataTree*> previousInstances;
        static AbstractDataTree* current;
        void drawElements();
        void drawNothing();
        AbstractDataTree() {
            drawFunction = &AbstractDataTree::drawElements;
        }
};

#endif // ABSTRACTDATATREE_H
