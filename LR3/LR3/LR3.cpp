#include<stdio.h>
#include<iostream>
#include <winsock2.h>
using namespace std;

struct tovar
{
	char firm[20];
	char country[20];
	char name[20];
	char col[20];
};
DWORD WINAPI ThreadFunc(LPVOID client_socket)
{
	tovar N[5];
	strcpy(N[0].country, "Germany\n");
	strcpy(N[0].firm, "Adidas\n");
	strcpy(N[0].name, "Trainers\n");
	strcpy(N[0].col, "200\n");
	strcpy(N[1].country, "England\n");
	strcpy(N[1].firm, "Reebok\n");
	strcpy(N[1].name, "T-shirts\n");
	strcpy(N[1].col, "300\n");
	strcpy(N[2].country, "France\n");
	strcpy(N[2].firm, "Balenciaga\n");
	strcpy(N[2].name, "Bag\n");
	strcpy(N[2].col, "500\n");
	strcpy(N[3].country, "Switzerland\n");
	strcpy(N[3].firm, "Rolex\n");
	strcpy(N[3].name, "Watch\n");
	strcpy(N[3].col, "100\n");
	strcpy(N[4].country, "Netherlands\n");
	strcpy(N[4].firm, "Mexx\n");
	strcpy(N[4].name, "Parfume\n");
	strcpy(N[4].col, "600\n");
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char buf[100];
	char buf1[100];
	//send(s2,"Welcome new client!\n",sizeof("Welcome new client!\n"),0);
	while (recv(s2, buf, sizeof(buf), 0))
	{	
		int nb=0;
		 int k = strlen(buf) - 1;
		
			for (int i = 0;i<5;i++)
			{
				if( strcmp(buf,N[i].country)==0)
				{
					
					for(int n=0; N[i].country[n]!='\0';n++,nb++)
					{
						buf1[nb] = N[i].country[n];
					}
					for (int n = 0; N[i].name[n] != '\0'; n++, nb++)
					{
						buf1[nb] = N[i].name[n];
					}
					for (int n = 0; N[i].firm[n] != '\0'; n++, nb++)
					{
						buf1[nb] = N[i].firm[n];
					}
					
					for (int n = 0; N[i].col[n] != '\0'; n++, nb++)
					{
						buf1[nb] = N[i].col[n];
					}
					break;
				}
			}
		
			buf1[nb] = '\0';
			strcpy(buf, buf1);
	
		cout << buf << endl;
		send(s2, buf, 100, 0);
	}
	closesocket(s2);
	return 0;
}

int numcl = 0;

void print()
{
	if (numcl) printf("%d client connected\n", numcl);
	else printf("No clients connected\n");
}

void main()
{
	
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)& local_addr, sizeof(local_addr));
	int c = listen(s, 5);
	cout << "Server receive ready" << endl;
	cout << endl;
	// извлекаем сообщение из очереди
	SOCKET client_socket;    // сокет для клиента
	sockaddr_in client_addr; // адрес клиента (заполняется системой)
	int client_addr_size = sizeof(client_addr);
	// цикл извлечения запросов на подключение из очереди
	while ((client_socket = accept(s, (sockaddr*)& client_addr, &client_addr_size)))
	{
		numcl++;
		print();
		// вызов нового потока для обслуживания клиента
		DWORD thID;  //thID идентификатор типа DWORD
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL,
			&thID);
	}
}
