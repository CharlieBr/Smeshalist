#include "WindowsDataTree.h"

AbstractDataTree* AbstractDataTree::active = new WindowsDataTree();

void WindowsDataTree::LOCK()
{
	WaitForSingleObject(mutex, INFINITY);
}

void WindowsDataTree::UNLOCK()
{
	ReleaseMutex(mutex);
}

void WindowsDataTree::sleepThread(int milisec) {
	Sleep(milisec);
}

void WindowsDataTree::createNewInstance() {
	LOCK();
	WindowsDataTree* newInstance = new WindowsDataTree();
	cloneDataTreeToNewInstance(newInstance);
	UNLOCK();
}