//
// Created by Fedya on 19.04.2021.
//

#ifndef CODE_TEAM_PROTOCOLS_H
#define CODE_TEAM_PROTOCOLS_H
#include <cassert>
#include "ServerConnection.h"
#include "Tool.h"

struct protocol {
    ServerConnection s;
    protocol(std::vector<SOCKET>& v, SOCKET& listensock): s(&v) {
        s.connect(listensock);
    }
    static void SendTool(Tool &t, SOCKET& sock) {
        t.serialize(sock);
    }

    static Tool *GetTool(SOCKET& Clsock) {
        std::string str = ServerConnection::GetString(Clsock);
        Tool *t;
        if (str == "Button") {
            t = new Button("");
        }
        if (str == "Slider") {
            t = new Slider("");
        }
        if (str == "Dial") {
            t = new Dial("");
        }
        if (str == "CMD") {
            t = new CMD("");
        }

        if (!t)
            throw 6;
        t->deserialize(Clsock);
        return t;
    }
    static void send_string(const std::string &str, SOCKET& Clsock) {
        ServerConnection::SendString(str, Clsock);
    }
    static std::string get_string( SOCKET& Clsock) {
        return ServerConnection::GetString(Clsock);
    }
    static int get_int( SOCKET& Clsock) {
        return ServerConnection::GetInt(Clsock);
    }
    static void send_int(int x,  SOCKET& Clsock) {
        ServerConnection::SendInt(x, Clsock);
    }
};
#endif  // CODE_TEAM_PROTOCOLS_H
