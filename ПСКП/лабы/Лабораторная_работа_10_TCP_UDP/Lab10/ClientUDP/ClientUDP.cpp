// ClientUDP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include "Winsock2.h"

#pragma comment(lib, "WS2_32.lib")

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

void Print(char ibuf[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (ibuf[i] == '\0')
		{
			break;
		}
		std::cout << ibuf[i];
	}
	std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    WSAData wsaData;
    SOCKET clientSocket;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
        {
            throw SetErrorMsgText("Startup: ", WSAGetLastError());
        }
        if ((clientSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
        {
            throw SetErrorMsgText("Socket: ", WSAGetLastError());
        }

        SOCKADDR_IN server;
        server.sin_family = AF_INET;
        server.sin_port = htons(40000);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

		int lServer = sizeof(server);
		char obuf[] = "Hello from client";
		char message[50] = "";

		while (true)
		{
			if ((sendto(clientSocket, obuf, strlen(obuf) + 1, NULL, (sockaddr*)&server, sizeof(server))) == SOCKET_ERROR)
			{
				throw SetErrorMsgText("sendto: ", WSAGetLastError());
			}
			if ((recvfrom(clientSocket, message, sizeof(message), NULL, (sockaddr*)&server, &lServer) == SOCKET_ERROR))
			{
				throw  SetErrorMsgText("recvfrom:", WSAGetLastError());
			}

			cout << "Response from server: " << message << endl;
		}

        if (closesocket(clientSocket) == SOCKET_ERROR)
        {
            throw SetErrorMsgText("closeSocket: ", WSAGetLastError());
        }
        if (WSACleanup() == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
        }

    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }
    cout << endl << endl;
    system("pause");
    return 0;
}