//
// Created by Fedya on 19.04.2021.
//
#include "ServerConnection.h"
#include <cassert>
#include <vector>

int ServerConnection::connect(SOCKET& ListenSocket) {
    WSADATA wsaData;

//    auto ListenSocket = INVALID_SOCKET;

    struct addrinfo *result = nullptr;
    struct addrinfo hints;

    //    char recvbuf[DEFAULT_BUFLEN]{};
    //    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
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
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket =
        socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    for (int i = 0; i < 1; ++i) {
        std::cout << "want to go " << i + 1 << "\n";
        ClientSockets->push_back(accept(ListenSocket, NULL, NULL));
        std::cout << "got one: " << i + 1 << "\n";
    }

    //    if (ClientSocket() == INVALID_SOCKET) {
    //        printf("accept failed with error: %d\n", WSAGetLastError());
    //        closesocket(ListenSocket);
    //        WSACleanup();
    //        return 1;
    //    }

    return 0;
}

int ServerConnection::shut_down(SOCKET &ClientSocket) {
    iResult = 0;
    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}

std::string ServerConnection::GetString(SOCKET &ClientSocket, bool wait) {
    int size = 0;
    auto iResult = 0;

    do {
        Sleep(100);
        iResult =
            recv(ClientSocket, reinterpret_cast<char *>(&size), sizeof(int), 0);
    } while (iResult == 0 && wait);
    size = ntohs(size);
    std::vector<char> buf;
    buf.resize(size + 1);
    if (iResult > 0) {
        iResult = recv(ClientSocket, &(buf[0]), size, 0);
    }
    std::string ans(&buf[0], size);
    /* if (iResult > 0) {
         std::cout << "Bytes received: " << iResult << "\n";
         std::cout << ans << "\n";
     }*/
    if (iResult < 0) {
        //        throw 1;
        std::cerr << "No connection\n";
    }
    return ans;
}

int ServerConnection::GetInt(SOCKET &ClientSocket) {
    int num;
    int result = 0;
    while (result == 0) {
        result =
            recv(ClientSocket, reinterpret_cast<char *>(&num), sizeof(int), 0);
    }
    if (result == -1) {
        std::cout << "end of talking!\n";
    }
    num = ntohs(num);
    return num;
}

int ServerConnection::SendString(const std::string &str, SOCKET &CLientSocket) {
    auto iResult = 0;
    // Send an initial buffer
    int size = str.size();
    size = htons(size);
    iResult = ::send(CLientSocket, reinterpret_cast<const char *>(&size),
                     (int)sizeof(int), 0);
    if (iResult == SOCKET_ERROR)
        return 1;
    iResult = ::send(CLientSocket, str.c_str(), str.size(), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(CLientSocket);
        WSACleanup();
        return 1;
    }

    // printf("Bytes Sent: %ld\n", iResult);
    return 0;
}

int ServerConnection::SendInt(const int number, SOCKET &ClientSocket) {
    int temnumber = number;
    std::cout << " SendInt: " << number << "\n";
    temnumber = htons(temnumber);
    send(ClientSocket, reinterpret_cast<const char *>(&temnumber), sizeof(int),
         0);
    return 0;
}
ServerConnection::ServerConnection(std::vector<SOCKET> *vec)
    : ClientSockets(vec) {
}
