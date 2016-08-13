#ifndef TYPESFILTER_H
#define TYPESFILTER_H

#include <string>
#include <algorithm>
#include "Data.h"

using namespace std;

class SingleTypesFilter
{
    string type;

    public:
        SingleTypesFilter(string type) {
            this -> type = type;
        }

        string getTypeName() {
            return type;
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
