//
// Created by Fedya on 19.04.2021.
//

#ifndef SERVER_SERVERCONNECTION_H
#define SERVER_SERVERCONNECTION_H
#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>
//#pragma comment(lib, "Ws2_32.lib") i dont know why it`s not working with that
// if one day everything crashed this may be a good thing to look at
#define DEFAULT_BUFLEN 512
class Tool;
struct ServerConnection
{
    ServerConnection(SOCKET clientSocket);

    int GetInt() const;
    int SendInt(int val) const;
    std::string GetString(bool wait = true) const;
    int SendString(const std::string &str) const;
    std::unique_ptr<Tool> GetTool() const;
    void SendTool(const Tool &t) const;

    SOCKET clientSocket_;
};
#endif//SERVER_SERVERCONNECTION_H
