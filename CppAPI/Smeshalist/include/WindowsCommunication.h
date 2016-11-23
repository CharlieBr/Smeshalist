#ifndef WINDOWS_COMMUNICATION_H
#define WINDOWS_COMMUNICATION_H

#include "AbstractCommunication.h"

#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <cstring>

using namespace std;

class WindowsCommunication : public AbstractCommuniation {
	public:
		WindowsCommunication();
		WindowsCommunication(int port_number);
		void SetupSocket();
		void CleanupSocket();
		int SendBytesToCore(const void* buffer, int buffer_size) const;
		int GetBytesFromCore(char* buffer, int buffer_size);
};

#endif // WINDOWS_COMMUNICATION_H
