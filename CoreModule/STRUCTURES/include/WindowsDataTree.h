#ifndef WINDOWSDATATREE_H
#define WINDOWSDATATREE_H

#include "AbstractDataTree.h"
#include <Windows.h>

class WindowsDataTree : public AbstractDataTree {
	public:
		static WindowsDataTree& getInstance();
	private:
		void LOCK();
		void UNLOCK();
		WindowsDataTree() {
			mutex = CreateMutex(NULL, FALSE, NULL);
			if (mutex == NULL) {
				cerr << "Windows mutex cannot be created!!!\n";
			}
		}

		HANDLE mutex;
};

#endif WINDOWSDATATREE_H