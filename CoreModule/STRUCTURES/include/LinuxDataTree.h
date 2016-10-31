#ifndef LINUXDATATREE_H
#define LINUXDATATREE_H

#include "AbstractDataTree.h"
#include <mutex>
#include <unistd.h>


class LinuxDataTree : public AbstractDataTree
{
    public:
        void createNewInstance();
    protected:
        void LOCK();
        void UNLOCK();
        void sleepThread(int);
    private:
        std::mutex mtx;
};

#endif // LINUXDATATREE_H
