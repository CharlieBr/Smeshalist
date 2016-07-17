#include "LinuxDataTree.h"

LinuxDataTree& LinuxDataTree::getInstance(){
    static LinuxDataTree instance;
    return instance;
}

void LinuxDataTree::LOCK() {
    mtx.lock();
}

void LinuxDataTree::UNLOCK() {
    mtx.unlock();
}
