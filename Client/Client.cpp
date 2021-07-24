#include "includes.h"

#pragma warning(disable:4996)
SOCKET Connection;

void Handler()
{
	char msg[256];
	while (true)
	{
		recv(Connection, msg, sizeof(msg), NULL);
		cout << msg << endl;
	}
}

int main(int argc, char* argv[])
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error #1" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("26.137.156.98");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	else
	{
		std::cout << "Yes I did it!!!";
	}


	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Handler, NULL, NULL, NULL);

	char msgl[256];
	while (true)
	{
		cin.getline(msgl, sizeof(msgl));
		send(Connection, msgl, sizeof(msgl), NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}