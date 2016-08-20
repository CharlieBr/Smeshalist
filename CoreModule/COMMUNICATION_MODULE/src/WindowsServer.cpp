#include "WindowsServer.h"

WindowsServer::WindowsServer() {
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "WSAStartup failed!!!\n";
	}

	sock = *createSocket(&sockaddr, PORT);
	sockSM = *createSocket(&sockaddrSM, 8393);

	slen = sizeof(client);
	isStopped.store(false);
}

SOCKET* WindowsServer::createSocket(sockaddr_in* sockaddr, int port) {
	SOCKET sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		cerr << "Could not create socket!!!\n";
	}

	sockaddr -> sin_family = AF_INET;
	sockaddr -> sin_addr.s_addr = inet_addr(IPADDRESS);
	sockaddr -> sin_port = htons(port);

	if (::bind(sock, (struct sockaddr*) sockaddr, sizeof(*sockaddr)) == SOCKET_ERROR) {
		cerr << "Could not bind the socket!!!\n";
	}

	return &sock;
}

void WindowsServer::startServer() {
	t = new thread(&WindowsServer::startServerInNewThread, this);
	tSM = new thread(&WindowsServer::startSMServer, this);
}

void WindowsServer::stopServer() {
	if (!isStopped.load()) {
		isStopped.store(true);
		t->join();
		tSM->join();
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

int WindowsServer::getBytesFromSMsocket(char buffer[], int bufferSize)
{
	return recvfrom(sockSM, buffer, bufferSize, 0, &clientSM, &slen);
}

int WindowsServer::sendBytesToSMsocket(char buffer[], int bufferSize)
{
	return sendto(sockSM, buffer, bufferSize, 0, &clientSM, slen);
}
