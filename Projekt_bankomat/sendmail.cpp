#include <winsock.h>
#include <stdio.h>
#include <windows.h>

#include "sendmail.h"
#include "base64.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;


int mail(std::string to, std::string subject, std::string body)
{
    const std::string host = "poczta.o2.pl";  //tutaj wpisz hosta szkrzynki z ktorej chcesz wyslac

    const std::string log = "bankomat.projekt@o2.pl";   //login do skrzynki
    const std::string pass = "bankomat";    //haslo do skrzynki

    const std::string sender = log;
    const std::string recipient = to;

    body = "From: Bankomat <" + sender + ">"
        "\nSubject: " + subject +
        "\nTo: <" + to + ">"
        "\n\n" + body;

    const int bufsize = 1024;
    char response[bufsize];


    std::string login = base64_encode(reinterpret_cast<const unsigned char*> (log.c_str()), log.length());
    std::string password = base64_encode(reinterpret_cast<const unsigned char*> (pass.c_str()), pass.length());


    WORD sockV;
    WSAData wsaData;
    int nret;

    sockV = MAKEWORD(2, 2);
    WSAStartup(sockV, &wsaData);
    LPHOSTENT hostEntry;
    hostEntry = gethostbyname(host.c_str());

    if (!hostEntry)
    {
        WSACleanup();
        return 0;
    }
    SOCKET CData;
    CData = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (CData == INVALID_SOCKET)
    {
        WSACleanup();
        return 0;
    }

    SOCKADDR_IN ServerInfo;
    ServerInfo.sin_family = AF_INET;
    ServerInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
    ServerInfo.sin_port = htons(25);
    nret = connect(CData, (LPSOCKADDR)&ServerInfo, sizeof(struct sockaddr));

    while (nret == SOCKET_ERROR)
    {
        nret = connect(CData, (LPSOCKADDR)&ServerInfo, sizeof(struct sockaddr));
    }

    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);
    //pierwsza odpowiedź od serwera

    //wiadomość powitalna
    send(CData, ("ehlo " + host + "\r\n").c_str(), ("ehlo " + host + "\r\n").length(), 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);

    //autoryzacja - prośba
    send(CData, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);

    //wysyłam login w base64
    send(CData, (login + "\r\n").c_str(), login.length() + 2, 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);

    //wysyłam password w base64
    send(CData, (password + "\r\n").c_str(), password.length() + 2, 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);


    //wysyłam nadawcę
    send(CData, ("MAIL FROM: <" + log + ">\r\n").c_str(), ("MAIL FROM: <" + log + ">\r\n").length(), 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);

    //wysyłam odbiorce
    send(CData, ("RCPT TO: <" + recipient + ">\r\n").c_str(), ("RCPT TO: <" + recipient + ">\r\n").length(), 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);
    //można ten krok powtórzyc, aby było ich więcej


    //rozpoczynam wysłanie wiadomosci
    send(CData, "DATA\r\n", 6, 0);
    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);

    send(CData, body.c_str(), body.length(), 0);
    send(CData, "\r\n.\r\n", 5, 0);
    //tekst i zakończenie speclalnymi zankami

    recv(CData, response, bufsize, 0);

    memset(&response, 0, bufsize);

    //	koniec!
    send(CData, "quit\r\n", 6, 0);
    recv(CData, response, bufsize, 0);


    return 1;
}
