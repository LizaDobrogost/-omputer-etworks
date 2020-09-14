// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include <winsock2.h>
#include <iostream>
using namespace std;
int main() {

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) return -1;

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	connect(s, (struct sockaddr*) & peer, sizeof(peer));

	char b[200], buf[200];

	recv(s, b, sizeof(b), 0);
	cout << b;
	b[0] = '\0';
	while (strcmp(b, "quit")) {
		cin.getline(b, 200, '\n');
		send(s, b, sizeof(b), 0);
	}

	WSACleanup();
	return 0;
}
