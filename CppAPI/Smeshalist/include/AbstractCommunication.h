#ifndef ABSTRACT_COMMUNICATION_H
#define ABSTRACT_COMMUNICATION_H

#include <cerrno>
#include <cstdio>
#include <cstring>

#define CORE_PORT 8383

using namespace std;

class AbstractCommuniation {
	public:
		AbstractCommuniation();
		AbstractCommuniation(int port_number);
		virtual void SetupSocket() = 0;
		virtual void CleanupSocket() = 0;
		virtual int SendBytesToCore(const void* buffer, int buffer_size) const = 0;
		virtual int GetBytesFromCore(char* buffer, int buffer_size) = 0;
	protected:
		int core_port;
};

#endif // ABSTRACT_COMMUNICATION_H

