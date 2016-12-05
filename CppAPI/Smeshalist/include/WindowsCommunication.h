#ifndef WINDOWS_COMMUNICATION_H
#define WINDOWS_COMMUNICATION_H

#include "AbstractCommunication.h"

#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class WindowsCommunication : public AbstractCommuniation {
	public:
		WindowsCommunication();
		WindowsCommunication(int port_number);
		void SetupSocket();
		void CleanupSocket();
		int SendBytesToCore(const char* buffer, int buffer_size) const;
		int GetBytesFromCore(char* buffer, int buffer_size);
    private:
		SOCKET* createSocket(sockaddr_in*, int);

		SOCKET core_socket;
		WSADATA wsa;
		struct sockaddr_in core_addr_in;
        int core_addr_size;
};

#endif // WINDOWS_COMMUNICATION_H
