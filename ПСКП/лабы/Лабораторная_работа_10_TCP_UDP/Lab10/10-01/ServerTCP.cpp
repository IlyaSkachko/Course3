
#include "ServerTCP.h"


using namespace std;




string GetErrorMsgText(int code)
{
	string message;

	switch (code)
	{
	case WSAEINTR:					message = "Работа функции прервана";  break;
	case WSAEACCES:					message = "Разрешение отвергнуто"; break;
	case WSAEFAULT:					message = "Ошибочный адрес"; break;
	case WSAEINVAL:					message = "Ошибка в аргументе"; break;
	case WSAEMFILE:					message = "Слишком много файлов открыто"; break;
	case WSAEWOULDBLOCK:			message = "Ресурс временно недоступен"; break;
	case WSAEINPROGRESS:			message = "Операция в процессе развития"; break;
	case WSAEALREADY:				message = "Операция уже выполняется"; break;
	case WSAENOTSOCK:				message = "Сокет задан неправильно"; break;
	case WSAEDESTADDRREQ:			message = "Требуется адрес расположения"; break;
	case WSAEMSGSIZE:				message = "Сообщение слишком длинное"; break;
	case WSAEPROTOTYPE:				message = "Неправильный тип протокола для сокета"; break;
	case WSAENOPROTOOPT:			message = "Ошибка в опции протокола"; break;
	case WSAEPROTONOSUPPORT:		message = "Протокол не поддерживается"; break;
	case WSAESOCKTNOSUPPORT:		message = "Тип сокета не поддерживается"; break;
	case WSAEOPNOTSUPP:				message = "Операция не поддерживается"; break;
	case WSAEPFNOSUPPORT:			message = "Тип протоколов не поддерживается"; break;
	case WSAEAFNOSUPPORT:			message = "Тип адресов не поддерживается протоколом"; break;
	case WSAEADDRINUSE:				message = "Адрес уже используется"; break;
	case WSAEADDRNOTAVAIL:			message = "Запрошенный адрес не может быть использован"; break;
	case WSAENETDOWN:				message = "Сеть отключена"; break;
	case WSAENETUNREACH:			message = "Сеть не достижима"; break;
	case WSAENETRESET:				message = "Сеть разорвала соединение"; break;
	case WSAECONNABORTED:			message = "Программный отказ связи"; break;
	case WSAECONNRESET:				message = "Связь восстановлена"; break;
	case WSAENOBUFS:				message = "Не хватает памяти для буферов"; break;
	case WSAEISCONN:				message = "Сокет уже подключен"; break;
	case WSAENOTCONN:				message = "Сокет не подключен"; break;
	case WSAESHUTDOWN:				message = "Нельзя выполнить send : сокет завершил работу"; break;
	case WSAETIMEDOUT:				message = "Закончился отведенный интервал времени"; break;
	case WSAECONNREFUSED:			message = "Соединение отклонено"; break;
	case WSAEHOSTDOWN:				message = "Хост в неработоспособном состоянии"; break;
	case WSAEHOSTUNREACH:			message = "Нет маршрута для хоста"; break;
	case WSAEPROCLIM:				message = "Слишком много процессов"; break;
	case WSASYSNOTREADY:			message = "Сеть не доступна"; break;
	case WSAVERNOTSUPPORTED:		message = "Данная версия недоступна"; break;
	case WSANOTINITIALISED:			message = "Не выполнена инициализация WS2_32.DLL"; break;
	case WSAEDISCON:				message = "Выполняется отключение"; break;
	case WSATYPE_NOT_FOUND:			message = "Класс не найден"; break;
	case WSAHOST_NOT_FOUND:			message = "Хост не найден"; break;
	case WSATRY_AGAIN:				message = "Неавторизированный хост не найден"; break;
	case WSANO_RECOVERY:			message = "Неопределенная ошибка"; break;
	case WSANO_DATA:				message = "Нет записи запрошенного типа"; break;
	case WSA_INVALID_HANDLE:		message = "Указанный дескриптор события с ошибкой"; break;
	case WSA_INVALID_PARAMETER:		message = "Один или более параметров с ошибкой"; break;
	case WSA_IO_INCOMPLETE:			message = "Объект ввода-вывода не в сигнальном состоянии"; break;
	case WSA_IO_PENDING:			message = "Операция завершится позже"; break;
	case WSA_NOT_ENOUGH_MEMORY:		message = "Не достаточно памяти"; break;
	case WSA_OPERATION_ABORTED:		message = "Операция отвергнута"; break;
	case WSASYSCALLFAILURE:			message = "Аварийное завершение системного вызова"; break;
	default: message = "***Ошибка***";  break;
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

