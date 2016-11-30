#ifndef WINDOWSDATATREE_H
#define WINDOWSDATATREE_H

#include "AbstractDataTree.h"
#include <Windows.h>

class WindowsDataTree : public AbstractDataTree {
	public:
		void createNewInstance();
		WindowsDataTree(string name) : AbstractDataTree(name){
			mutex = CreateMutex(NULL, FALSE, NULL);
			if (mutex == NULL) {
				cerr << "Windows mutex cannot be created!!!\n";
			}
		}
	protected:
		void LOCK();
		void UNLOCK();
		void sleepThread(int);	
	private:
		HANDLE mutex;
};

#endif WINDOWSDATATREE_H