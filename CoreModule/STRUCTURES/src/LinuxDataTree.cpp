#include "LinuxDataTree.h"

AbstractDataTree* AbstractDataTree::current = new LinuxDataTree();

void LinuxDataTree::LOCK() {
    mtx.lock();
}

void LinuxDataTree::UNLOCK() {
    mtx.unlock();
}

void LinuxDataTree::sleepThread(int milisec) {
    if (usleep(milisec*1000) != 0) {
        cerr << "Error during waiting for posibility to clean data tree\n";
    }
}

void LinuxDataTree::createNewInstance() {
    LOCK();
    LinuxDataTree* newInstance = new LinuxDataTree();
	cloneDataTreeToNewInstance(newInstance);
    UNLOCK();
}
