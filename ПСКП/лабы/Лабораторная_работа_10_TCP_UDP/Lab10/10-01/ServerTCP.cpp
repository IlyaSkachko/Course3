
#include "ServerTCP.h"


using namespace std;




string GetErrorMsgText(int code)
{
	string message;

	switch (code)
	{
	case WSAEINTR:					message = "������ ������� ��������";  break;
	case WSAEACCES:					message = "���������� ����������"; break;
	case WSAEFAULT:					message = "��������� �����"; break;
	case WSAEINVAL:					message = "������ � ���������"; break;
	case WSAEMFILE:					message = "������� ����� ������ �������"; break;
	case WSAEWOULDBLOCK:			message = "������ �������� ����������"; break;
	case WSAEINPROGRESS:			message = "�������� � �������� ��������"; break;
	case WSAEALREADY:				message = "�������� ��� �����������"; break;
	case WSAENOTSOCK:				message = "����� ����� �����������"; break;
	case WSAEDESTADDRREQ:			message = "��������� ����� ������������"; break;
	case WSAEMSGSIZE:				message = "��������� ������� �������"; break;
	case WSAEPROTOTYPE:				message = "������������ ��� ��������� ��� ������"; break;
	case WSAENOPROTOOPT:			message = "������ � ����� ���������"; break;
	case WSAEPROTONOSUPPORT:		message = "�������� �� ��������������"; break;
	case WSAESOCKTNOSUPPORT:		message = "��� ������ �� ��������������"; break;
	case WSAEOPNOTSUPP:				message = "�������� �� ��������������"; break;
	case WSAEPFNOSUPPORT:			message = "��� ���������� �� ��������������"; break;
	case WSAEAFNOSUPPORT:			message = "��� ������� �� �������������� ����������"; break;
	case WSAEADDRINUSE:				message = "����� ��� ������������"; break;
	case WSAEADDRNOTAVAIL:			message = "����������� ����� �� ����� ���� �����������"; break;
	case WSAENETDOWN:				message = "���� ���������"; break;
	case WSAENETUNREACH:			message = "���� �� ���������"; break;
	case WSAENETRESET:				message = "���� ��������� ����������"; break;
	case WSAECONNABORTED:			message = "����������� ����� �����"; break;
	case WSAECONNRESET:				message = "����� �������������"; break;
	case WSAENOBUFS:				message = "�� ������� ������ ��� �������"; break;
	case WSAEISCONN:				message = "����� ��� ���������"; break;
	case WSAENOTCONN:				message = "����� �� ���������"; break;
	case WSAESHUTDOWN:				message = "������ ��������� send : ����� �������� ������"; break;
	case WSAETIMEDOUT:				message = "���������� ���������� �������� �������"; break;
	case WSAECONNREFUSED:			message = "���������� ���������"; break;
	case WSAEHOSTDOWN:				message = "���� � ����������������� ���������"; break;
	case WSAEHOSTUNREACH:			message = "��� �������� ��� �����"; break;
	case WSAEPROCLIM:				message = "������� ����� ���������"; break;
	case WSASYSNOTREADY:			message = "���� �� ��������"; break;
	case WSAVERNOTSUPPORTED:		message = "������ ������ ����������"; break;
	case WSANOTINITIALISED:			message = "�� ��������� ������������� WS2_32.DLL"; break;
	case WSAEDISCON:				message = "����������� ����������"; break;
	case WSATYPE_NOT_FOUND:			message = "����� �� ������"; break;
	case WSAHOST_NOT_FOUND:			message = "���� �� ������"; break;
	case WSATRY_AGAIN:				message = "������������������ ���� �� ������"; break;
	case WSANO_RECOVERY:			message = "�������������� ������"; break;
	case WSANO_DATA:				message = "��� ������ ������������ ����"; break;
	case WSA_INVALID_HANDLE:		message = "��������� ���������� ������� � �������"; break;
	case WSA_INVALID_PARAMETER:		message = "���� ��� ����� ���������� � �������"; break;
	case WSA_IO_INCOMPLETE:			message = "������ �����-������ �� � ���������� ���������"; break;
	case WSA_IO_PENDING:			message = "�������� ���������� �����"; break;
	case WSA_NOT_ENOUGH_MEMORY:		message = "�� ���������� ������"; break;
	case WSA_OPERATION_ABORTED:		message = "�������� ����������"; break;
	case WSASYSCALLFAILURE:			message = "��������� ���������� ���������� ������"; break;
	default: message = "***������***";  break;
	}

	return message;
}

string SetErrorMsgText(string message, int code)
{
	return message + GetErrorMsgText(code);
}




int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	WSAData wsaData;
	SOCKET serverSocket;
	try
	{

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		{
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		}
		if ((serverSocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
		{
			throw SetErrorMsgText("Socket: ", WSAGetLastError());
		}

		SOCKADDR_IN server;											
		server.sin_family = AF_INET;								
		server.sin_port = htons(40000);								
		server.sin_addr.s_addr = INADDR_ANY;						



		if (bind(serverSocket, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR)
		{
			throw SetErrorMsgText("bind: ", WSAGetLastError());
		}
		if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			throw SetErrorMsgText("listen: ", WSAGetLastError());
		}

		SOCKET clientSocket;
		SOCKADDR_IN client;
		memset(&client, 0, sizeof(client));
		int lClient = sizeof(client);
		
		while (true)
		{

			cout << "\nServer start listening...\n\n\n";

			if ((clientSocket = accept(serverSocket, (sockaddr*)&client, &lClient)) == INVALID_SOCKET)
			{
				throw SetErrorMsgText("accept: ", WSAGetLastError());
			}

			cout << "\nClient IP-adress: " << inet_ntoa(client.sin_addr)
				<< "\nClient Port: " << htons(client.sin_port) << endl;

			int libuf = 1;
			char obuf[] = "Hello from Client";

			while (libuf != 0)
			{
				if ((libuf = recv(clientSocket, obuf, sizeof(obuf), NULL)) == SOCKET_ERROR)
				{
					throw  SetErrorMsgText("recv:", WSAGetLastError());
				}

				if (libuf == 0)
					break;

				char ibuf[25] = "";
				strcat_s(ibuf, "ECHO ");
				strcat_s(ibuf, obuf);

				if ((send(clientSocket, ibuf, strlen(ibuf) + 1, NULL)) == SOCKET_ERROR)
				{
					throw  SetErrorMsgText("send:", WSAGetLastError());
				}

				std::cout << std::endl << "Client message: " << obuf;

			}

		}

		if (closesocket(serverSocket) == SOCKET_ERROR)
		{
			throw SetErrorMsgText("Close Socket: ", WSAGetLastError());
		}
		if (closesocket(clientSocket) == SOCKET_ERROR)
		{
			throw SetErrorMsgText("Close Socket: ", WSAGetLastError());
		}
		if (WSACleanup() == SOCKET_ERROR)
		{
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
		}

	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError:" << errorMsgText;
	}


	system("pause");
	return 0;
}

