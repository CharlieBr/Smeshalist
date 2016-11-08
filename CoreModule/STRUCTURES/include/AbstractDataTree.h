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
        static void recomputeIntersectionPointsInVisibleTree();
        static void reloadFlitersInAllTrees(vector<SingleGroupFilter*>*, vector<SingleTypesFilter*>*, vector<SingleCoordinateFilter*>*, LogicalConnectiveEnum*, vector<SingleQualityFilter*>*);
        static int getNumberOfDataTreeInstances();
        virtual void createNewInstance() = 0;
        static AbstractDataTree* getCurrentlyVisibleDataTree();
        static AbstractDataTree* getActiveDataTree();
        static int getVisibleDataTreeIndex();
        static void decreaseVisibleDataTreeIndex();
        static void increaseVisibleDataTreeIndex();
        static bool isActiveTreeVisible();
        void draw_elements();
        void clean();
    protected:
        virtual void LOCK()=0;
        virtual void UNLOCK()=0;
        virtual void sleepThread(int)=0;
		void cloneDataTreeToNewInstance(AbstractDataTree*);
        void (AbstractDataTree::*drawFunction)();
        void filterDataTree();
        void recomputeIntersectionPoints();
        void reloadFliters(vector<SingleGroupFilter*>*, vector<SingleTypesFilter*>*, vector<SingleCoordinateFilter*>*, LogicalConnectiveEnum*, vector<SingleQualityFilter*>*);
        static AbstractDataTree* getDataTreeInstance(int);
        static vector<AbstractDataTree*> previousInstances;
        static AbstractDataTree* active;
        static bool readyToBeCleaned;
        static int visibleDataTreeIndex; //-1-current; >=0 - previous
        void drawElements();
        void drawNothing();
        AbstractDataTree() {
            drawFunction = &AbstractDataTree::drawElements;
        }
};

#endif // ABSTRACTDATATREE_H
