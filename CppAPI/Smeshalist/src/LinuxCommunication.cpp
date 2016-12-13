#include "LinuxCommunication.h"


LinuxCommunication::LinuxCommunication() : AbstractCommuniation() {
}

LinuxCommunication::LinuxCommunication(int port_number) : AbstractCommuniation(port_number) {
}

void LinuxCommunication::SetupSocket() {

	if ((core_socket = socket(AF_INET, SOCK_DGRAM, 0))  < 0) {
		perror("Cannot create socket");
		return;
	}

	memset((char *)&core_addr, 0, sizeof(core_addr));
	core_addr.sin_family = AF_INET;
	core_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	core_addr.sin_port = htons(core_port);

	struct timeval tv;
	tv.tv_sec = TIMEOUT_SEC;
	tv.tv_usec = TIMEOUT_USEC;

	if (setsockopt(core_socket,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
		perror("Cannot set timeout for recvfrom");
		return;
	}
}

void LinuxCommunication::CleanupSocket() {
	close(core_socket);
}

int LinuxCommunication::SendBytesToCore(const char* buffer, int buffer_size) const {

	return sendto(core_socket, buffer, buffer_size, 0, (struct sockaddr *)&core_addr, sizeof(core_addr));
}
int LinuxCommunication::GetBytesFromCore(char* buffer, int buffer_size) {
	int ret_val = recvfrom(core_socket, buffer, buffer_size, 0, (struct sockaddr *)&core_addr, &core_addr_size);
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
		throw CoreNotRunningException();
    }
	return ret_val;
}
