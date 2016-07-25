#include "WindowsDataTree.h"

WindowsDataTree& WindowsDataTree::getInstance()
{
	static WindowsDataTree instance;
	return instance;
}

void WindowsDataTree::LOCK()
{
	WaitForSingleObject(mutex, INFINITY);
}

void WindowsDataTree::UNLOCK()
{
	ReleaseMutex(mutex);
}
