#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <winsock2.h>
#include <experimental/filesystem>
#include <string>


struct Employee {
	char name[35];
	char position[10];
	char income[10];
	char dateofbirth[10];
} em[5];
char* fcvt(float v, int prec, int* point, int* sign)
{
	static char buf[32];
	char fmt[8],
		* r = buf;

	sprintf(fmt, "%%.%df", prec);
	sprintf(buf, fmt, v);
	*sign = 0;
	if (buf[0] == '-')
		* sign = 1, ++r;
	char* p = strchr(r, '.');
	if (p) {
		*point = p - r;
		for (int i = 1; p[i - 1] = p[i]; i++);
	}
	else
		*point = 0;

	return r;
}
// процедура для обслуживания соединения
int Func(int newS) {
	long int i, num, t, mon, doh, nal;
	float sum;
	int m;
	char p, p1, s;
	char buf[256], b[256];
	while (true) {
		recv(newS, buf, sizeof(buf), 0);
		p = buf[0];
		switch (p) {
		case '1':
			buf[0] = '\0';
			sum = 0;
			recv(newS, buf, sizeof(buf), 0);
			mon = atoi(buf);

	
			recv(newS, buf, sizeof(buf), 0);

			s = buf[0];
			for (i = 1; i <= 5; i++)
				if (em[i].name[0] == s) {
					nal = atoi(em[i].dateofbirth);
					doh = atoi(em[i].income);
					printf("mon %d\n", mon);
					sum = sum + (nal * doh * mon) / 100.0;
				}
			int* decpt, * sgn;
			printf("%f\n", sum);
			strcpy(buf, fcvt(sum, 3, decpt, sgn));
			send(newS, buf, sizeof(buf), 0);
			puts(buf);
			break;
		case '2':
			recv(newS, buf, sizeof(buf), 0);  //Номер
			num = atoi(buf);
			printf("%d\n", num);

			recv(newS, buf, sizeof(buf), 0);
			p1 = buf[0];
			switch (p1) {
			case '1':
				recv(newS, buf, sizeof(buf), 0); //Имя
				strcpy(em[num].name, buf);
				break;
			case	'2': recv(newS, buf, sizeof(buf), 0); //Таб.номер
				strcpy(em[num].position, buf);
				break;
			case '3':recv(newS, buf, sizeof(buf), 0); //Доход
				strcpy(em[num].income, buf);
				break;
			case '4': recv(newS, buf, sizeof(buf), 0); //Ставка налога
				strcpy(em[num].dateofbirth, buf);
			}
			break;
		case '3':
			for (i = 1; i <= 5; i++) {
				buf[0] = '\0';
				strcat(buf, em[i].name); strcat(buf, " ");
				strcat(buf, em[i].position); strcat(buf, " ");
				strcat(buf, em[i].income); strcat(buf, " ");
				strcat(buf, em[i].dateofbirth); strcat(buf, "\n");
				send(newS, buf, sizeof(buf), 0);
			}
			break;
		case '4':
			exit(0);

		}
	}
}
void reaper(int sig) {
	int status;
	//while (wait3(&status, WNOHANG, (struct rusage*)0) >= 0);
}

int main() {
	
	strcpy(em[1].name, "Sergeev Sergei Sergeevich");
	strcpy(em[1].position, "Manager");
	strcpy(em[1].income, "100000");
	strcpy(em[1].dateofbirth, "10.11.94");

	strcpy(em[2].name, "Ivanov Ivan Ivanovich");
	strcpy(em[2].position, "Salesman");
	strcpy(em[2].income, "20000");
	strcpy(em[2].dateofbirth, "20.06.93");

	strcpy(em[3].name, "Vladimirov Vladimir Vladmirvich");
	strcpy(em[3].position, "Programer");
	strcpy(em[3].income, "300000");
	strcpy(em[3].dateofbirth, "30.06.00");

	strcpy(em[4].name, "Sidorov Sidor Sidorovich ");
	strcpy(em[4].position, "Owner");
	strcpy(em[4].income, "4000000");
	strcpy(em[4].dateofbirth, "21.02.88");

	strcpy(em[5].name, "Vasilev Vasilii Vasilievich");
	strcpy(em[5].position, "Bank worker");
	strcpy(em[5].income, "50000");
	strcpy(em[5].dateofbirth, "14.04.90");

	struct sockaddr_in local;
	int s, newS, rc;
	std::string buf;
	local.sin_family = AF_INET;
	local.sin_port = htons(7500);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	s = socket(AF_INET, SOCK_STREAM, 0);
	rc = bind(s, (struct sockaddr*) & local, sizeof(local));
	rc = listen(s, 5);
	//(void)signal(SIGCHLD, reaper);
	while (true) {
		newS = accept(s, NULL, NULL);
		switch (newS) {
		case 0:
			(void)closesocket(s);
			exit(Func(newS));
		default:
			(void)closesocket(newS);
		}
	}

	return 0;
}


