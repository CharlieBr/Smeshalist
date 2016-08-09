#include "WindowsServer.h"

WindowsServer::WindowsServer() {
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "WSAStartup failed!!!\n";
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cerr << "Could not create socket!!!\n";
	}

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(IPADDRESS);
	sockaddr.sin_port = htons(PORT);

	if (::bind(sock, (struct sockaddr*) &sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
		cerr << "Could not bind the socket!!!\n";
	}

	slen = sizeof(client);
	isStopped.store(false);
}

void WindowsServer::startServer() {
	t = new thread(&WindowsServer::startServerInNewThread, this);
}

void WindowsServer::stopServer() {
	if (!isStopped.load()) {
		isStopped.store(true);
		t->join();
		closesocket(sock);
		WSACleanup();
	}
}

int WindowsServer::getBytesFromSocket(char buffer[], int bufferSize)
{
	return recvfrom(sock, buffer, bufferSize, 0, &client, &slen);
}

int WindowsServer::sendBytesToSocket(char buffer[], int bufferSize)
{
	return sendto(sock, buffer, bufferSize, 0, &client, slen);
}