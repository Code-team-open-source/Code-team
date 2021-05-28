//
// Created by Fedya on 19.04.2021.
//
#include "Server.h"
#include <stdio.h>
#include <cassert>
#include <mutex>
#include "InitialData.h"
#include <iostream>

static const char *DEFAULT_PORT = "27015";

CodeTeamServer::CodeTeamServer() {
    addrinfo *result = nullptr;
    addrinfo hints;

    // Initialize Winsock
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsaData_);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        throw 100;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        throw 1;
    }

    // Create a SOCKET for connecting to server
    listeningSocket_ =
        socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listeningSocket_ == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        throw 1;
    }

    // Setup the TCP listening socket
    iResult = bind(listeningSocket_, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        throw 1;
    }

    freeaddrinfo(result);
}

// void CodeTeamServer::setSink(IListenerSink *sink)
//{
//    sink_ = sink;
//}

void CodeTeamServer::listen(bool &continue_, std::mutex& m) {
    if (::listen(listeningSocket_, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        throw 1;
    }

    // Accept a client socket
    int count = 0;
//    select(0, &s_set, 0, 0, &timeout);
    for (;;) {
        _sleep(500);
        fd_set s_set = {1, {listeningSocket_}};
        timeval timeout = {0, 0};
//        _sleep(1000);
        if (!sink_->accept_players) {
            sink_->players_amount = count;
            break;
        }
        auto flag_ = select(0, &s_set, 0, 0, &timeout);
//        std::cout << "yyy" << sink_->accept_players << "\n" << flag_ << "\n";
        if (flag_ > 0) {
            std::cerr << "gotcha\n";
            auto client = accept(listeningSocket_, NULL, NULL);
            std::cerr << "accepted\n";
            sink_->accept(client);
            count++;
        }
        //        sink_->accept(client);

    }
}

CodeTeamServer::~CodeTeamServer() {
    // shutdown the connection since we're done
    if (shutdown(listeningSocket_, SD_SEND) == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
    }

    // cleanup
    closesocket(listeningSocket_);
    WSACleanup();
}

void CodeTeamServer::setSink(IListenerSink *sink) {
    sink_ = sink;
}
