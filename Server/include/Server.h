//
// Created by Fedya on 19.04.2021.
//

#ifndef SERVER_H
#define SERVER_H
#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <mutex>

struct IListenerSink
{
    virtual void accept(SOCKET s) = 0;
};

class CodeTeamServer
{
public:
    CodeTeamServer();
    void setSink( IListenerSink *sink );
    void listen(bool&, std::mutex&);
    ~CodeTeamServer();

private:
    WSADATA wsaData_;
    SOCKET listeningSocket_ = INVALID_SOCKET;
    IListenerSink *sink_;
};


#endif //SERVER_SH
