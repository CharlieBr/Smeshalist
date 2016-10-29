#ifndef GROUPSFILTER_H
#define GROUPSFILTER_H

#include <vector>
#include <algorithm>
#include "Data.h"

using namespace std;

class SingleGroupFilter
{
    int groupID;
    bool selected;

    public:
        SingleGroupFilter(int groupID, bool isSelected) {
            this -> groupID = groupID;
            this -> selected = isSelected;
        }

        int getGroupID() {
            return groupID;
        }

        bool isSelected() {
            return selected;
        }
};

class GroupsFilter
{
    public:
        static GroupsFilter* getInstance() {
            if (!instance) {
                instance = new GroupsFilter();
            }
            return instance;
        }
        void addSimpleGroupFilter(SingleGroupFilter*);
        void deleteAllFilters();
        void filterTree(Data*);
    protected:
    private:
        GroupsFilter(){};
        static GroupsFilter* instance;
        static vector<SingleGroupFilter*> filterList;
};


#endif // GROUPSFILTER_H
