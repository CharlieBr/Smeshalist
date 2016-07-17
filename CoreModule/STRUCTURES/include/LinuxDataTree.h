#ifndef LINUXDATATREE_H
#define LINUXDATATREE_H

#include "AbstractDataTree.h"
#include <mutex>


class LinuxDataTree : public AbstractDataTree
{
    public:
        static LinuxDataTree& getInstance();
    protected:
        void LOCK();
        void UNLOCK();
    private:
        std::mutex mtx;
};

#endif // LINUXDATATREE_H
