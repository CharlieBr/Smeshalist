#include "LinuxDataTree.h"

AbstractDataTree* AbstractDataTree::active = new LinuxDataTree("ACTIVE");

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
    char title[80];
    strcpy(title, "PREVIOUS: ");
    strcat(title, to_string(getNumberOfDataTreeInstances()+1).c_str());
    LinuxDataTree* newInstance = new LinuxDataTree(title);
	cloneDataTreeToNewInstance(newInstance);
    UNLOCK();
}
