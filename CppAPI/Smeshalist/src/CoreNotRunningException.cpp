#include "CoreNotRunningException.h"

const char* CoreNotRunningException::what() const throw() {
	string what = "Core module isn't running!\n";
	return what.c_str();
}