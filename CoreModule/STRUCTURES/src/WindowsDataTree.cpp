#include "WindowsDataTree.h"

AbstractDataTree* AbstractDataTree::active = new WindowsDataTree("ACTIVE");

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
	char title[80];
	strcpy(title, "PREVIOUS: ");
	strcat(title, to_string(getNumberOfDataTreeInstances() + 1).c_str());
	WindowsDataTree* newInstance = new WindowsDataTree(title);
	cloneDataTreeToNewInstance(newInstance);
	UNLOCK();
}