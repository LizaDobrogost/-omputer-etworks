#include<winsock2.h>
#include<iostream>
#include<stdlib.h>
#include <process.h>
#include <string>
using namespace std;

void main(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in ad;
	ad.sin_port = htons(1024);
	ad.sin_family = AF_INET;
	ad.sin_addr.s_addr = 0;//подставляет подходящий iр

	bind(s, (struct sockaddr*) & ad, sizeof(ad));

	char b[200], tmр = '\0';
	int l;
	l = sizeof(ad);
	int rv = recvfrom(s, b, lstrlen(b), 0, (struct  sockaddr*) & ad, &l);
	b[rv] = '\0';
	cout << b << endl;
	int kolvo=0;
	int len=strlen(b);
	if(len%5==0)
	{
		for (int i=0;i<len;i++)
		{
			if(b[i]=='{'||b[i]=='['||b[i]=='('||b[i]=='}'||b[i]==']'||b[i]==')')
			{
				kolvo++;
			}
		}
		
	}
	b[0] = kolvo+'0';
	b[1] = '\0';
	
	sendto(s, b, lstrlen(b), 0, (struct  sockaddr*) & ad, l);

	closesocket(s);
	WSACleanup();
}
