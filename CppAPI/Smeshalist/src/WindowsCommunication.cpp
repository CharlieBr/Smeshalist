#include "WindowsCommunication.h"

WindowsCommunication::WindowsCommunication() : AbstractCommuniation() {
}

WindowsCommunication::WindowsCommunication(int port_number) : AbstractCommuniation(port_number) {
}

void WindowsCommunication::SetupSocket() {

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            cerr << "WSAStartup failed!!!\n";
        }

        core_socket = *createSocket(&core_addr_in, core_port);
        core_addr_size = sizeof(core_addr_in);
}

void WindowsCommunication::CleanupSocket()
{
}

SOCKET* WindowsCommunication::createSocket(sockaddr_in* sockaddr, int port) {
	SOCKET sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cerr << "Could not create socket!!!\n";
	}

	sockaddr -> sin_family = AF_INET;
	sockaddr -> sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sockaddr -> sin_port = htons(port);

	return &sock;
}

int WindowsCommunication::GetBytesFromCore(char* buffer, int buffer_size) {
	
	fd_set fds;
	int n;
	struct timeval tv;

	// Set up the file descriptor set.
	FD_ZERO(&fds);
	FD_SET(core_socket, &fds);

	// Set up the struct timeval for the timeout.
	tv.tv_sec = TIMEOUT_SEC;
	tv.tv_usec = TIMEOUT_USEC;

	// Wait until timeout or data received.
	n = select(0, &fds, 0, 0, &tv);
	if (n == 0)	{
		throw CoreNotRunningException();
	}
	else if (n == -1)	{
		cerr << "Error when receiving from Core" << endl;
	}
	
    return recvfrom(core_socket, buffer, buffer_size, 0, (struct sockaddr*)&core_addr_in, &core_addr_size);
}

int WindowsCommunication::SendBytesToCore(const char* buffer, int buffer_size) const {
    return sendto(core_socket, buffer, buffer_size, 0, (struct sockaddr*)&core_addr_in, core_addr_size);
}
