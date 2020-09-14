#include <WinSock2.h>//интерфейс разработки приложений 
#include<iostream>
using namespace std;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData); 
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));
	int r = listen(s, 5);
	while (true)
	{
		char buf[255], res[100], b[255], *Res;
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		SOCKET s2 = accept(s, (struct sockaddr*)&remote_addr, &size);
		while (recv(s2, b, sizeof(b), 0) != 0)
		{
			int i = 0;
			for (unsigned j = 0; j <= strlen(b); j++)
				if ((int)b[j] % 3 == 0 && b[j] != '\0') i++;
			_itoa(i, res, 10);

			Res = new char[strlen(res) + 1];
			strcpy(Res, res);
			Res[strlen(res)] = '\0';


			//ѕосылает данные на соединенный сокет
			send(s2, Res, sizeof(Res) - 2, 0);
		}
		closesocket(s2);
		WSACleanup();
	}
}
