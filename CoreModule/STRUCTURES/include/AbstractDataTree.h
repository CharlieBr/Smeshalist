#ifndef ABSTRACTDATATREE_H
#define ABSTRACTDATATREE_H

#include "Data.h"


class AbstractDataTree : public Data
{
    public:
        static AbstractDataTree& getInstance();
        void add(int, Element*);
        void add(int, vector<Element*>*);
    protected:
    private:

};

#endif // ABSTRACTDATATREE_H
