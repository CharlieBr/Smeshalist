#ifndef CORE_NOT_RUNNING_EXCEPTION_H
#define CORE_NOT_RUNNING_EXCEPTION_H

#include<iostream>

using namespace std;

class CoreNotRunningException : public exception {
	public:
		virtual const char* what() const throw();
};

#endif