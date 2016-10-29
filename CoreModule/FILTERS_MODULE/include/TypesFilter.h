#ifndef TYPESFILTER_H
#define TYPESFILTER_H

#include <string>
#include <algorithm>
#include "Data.h"

using namespace std;

class SingleTypesFilter
{
    string type;
    bool selected;

    public:
        SingleTypesFilter(string type, bool isSelected) {
            this -> type = type;
            this -> selected = isSelected;
        }

        string getTypeName() {
            return type;
        }

        bool isSelected() {
            return selected;
        }
};


class TypesFilter
{
    public:
        static TypesFilter* getInstance() {
            if (!instance) {
                instance = new TypesFilter();
            }
            return instance;
        }
        void addSingleFilter(SingleTypesFilter*);
        void deleteAllFilters();
        void filterTree(Data*);
    protected:
    private:
        static TypesFilter* instance;
        static vector<SingleTypesFilter*> filterList;
};

#endif // TYPESFILTER_H
