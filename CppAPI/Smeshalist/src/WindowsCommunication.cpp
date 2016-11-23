#include "WindowsCommunication.h"

WindowsCommunication::WindowsCommunication() : AbstractCommuniation() {
}

WindowsCommunication::WindowsCommunication(int port_number) : AbstractCommuniation(port_number) {
}

void WindowsCommunication::SetupSocket() {

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            cerr << "WSAStartup failed!!!\n";
        }

        core_socket = *createSocket(&core_addr, core_port);
        core_addr_size = sizeof(core_addr);
}

SOCKET* WindowsCommunication::createSocket(sockaddr_in* sockaddr, int port) {
	SOCKET sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cerr << "Could not create socket!!!\n";
	}

	sockaddr -> sin_family = AF_INET;
	sockaddr -> sin_addr.s_addr = inet_addr(IPADDRESS);
	sockaddr -> sin_port = htons(port);

	return &sock;
}

int WindowsCommunication::GetBytesFromCore(char* buffer, int buffer_size) {
    return recvfrom(core_socket, buffer, buffer_size, 0, &core_addr, &core_addr_size);
}

int WindowsCommunication::SendBytesToCore(char* buffer, int buffer_size) {
    return sendto(core_socket, buffer, buffer_size, 0, &core_addr, core_addr_size);
}
