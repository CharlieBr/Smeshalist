#ifndef LINUX_COMMUNICATION_H
#define LINUX_COMMUNICATION_H

#include "AbstractCommunication.h"
#include "CoreNotRunningException.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <cstring>

using namespace std;

class LinuxCommunication : public AbstractCommuniation {
	public:
		LinuxCommunication();
		LinuxCommunication(int port_number);
		void SetupSocket();
		void CleanupSocket();
		int SendBytesToCore(const char* buffer, int buffer_size) const;
		int GetBytesFromCore(char* buffer, int buffer_size);
	private:
		struct sockaddr_in core_addr;
		socklen_t core_addr_size;
		int core_socket;

};

#endif // LINUX_COMMUNICATION_H
