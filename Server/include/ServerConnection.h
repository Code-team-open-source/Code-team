//
// Created by Fedya on 19.04.2021.
//

#ifndef SERVER_SERVERCONNECTION_H
#define SERVER_SERVERCONNECTION_H
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
//#pragma comment(lib, "Ws2_32.lib") i dont know why it`s not working with that
// if one day everything crashed this may be a good thing to look at
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
struct ServerConnection {
    int iResult = 0;
    int iSendResult = 0;
    SOCKET &ClientSocket() {
        static SOCKET ClientSocket;
        return ClientSocket;
    }
    int connect();
    std::string GetString(bool wait = 1);
    int GetInt();
    int SendString(const std::string &str);
    int SendInt(int);
    int shut_down();
};
#endif//SERVER_SERVERCONNECTION_H
