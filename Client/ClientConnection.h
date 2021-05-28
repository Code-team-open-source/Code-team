//
// Created by Fedya on 19.04.2021.
//

#ifndef CLIENT_CLIENTCONNECTION_H
#define CLIENT_CLIENTCONNECTION_H
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <QLabel>

struct Task;

//#include "mainwindow.h"

//#pragma comment(lib, "Ws2_32.lib") i dont know why it`s not working with that
// if one day everything crashed this may be a good thing to look at
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

struct ClientConnection {
    std::string ip;
    int iResult = 0;
    SOCKET ConnectSocket;
    int Connect();
    ClientConnection(std::string ip_ = "localhost") : ip(ip_) {
        Connect();
    }
    int SendString(const std::string &str);
    std::string GetString(bool flag = true);
    int SendInt(const int &a);
    int GetInt();
    int CloseSocket();
    Task *GetTool();

};

#endif//CLIENT_CLIENTCONNECTION_H
