//
// Created by Fedya on 19.04.2021.
//
#include "ClientConnection.h"

#include <string>
int ClientConnection::Connect() {
    WSADATA wsaData;
    ConnectSocket() = INVALID_SOCKET;
    struct addrinfo *result = nullptr,
            *ptr = nullptr,
            hints;
    //const char *sendbuf = "this is a test";

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket() = socket(ptr->ai_family, ptr->ai_socktype,
                                 ptr->ai_protocol);
        if (ConnectSocket() == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket(), ptr->ai_addr, (int) ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket());
            ConnectSocket() = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket() == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    return 0;
}

int ClientConnection::SendString(const std::string &str) {
    printf("sending string...\n");
    iResult = 0;
    // Send an initial buffer
    int size = str.size();
    size = htons(size);
    iResult = ::send(ConnectSocket(), reinterpret_cast<const char *>(&size), (int) sizeof(int), 0);
    if (iResult == SOCKET_ERROR)
        return 1;
    iResult = ::send(ConnectSocket(), str.c_str(), str.size(), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket());
        WSACleanup();
        return 1;
    }


    printf("Bytes Sent: %ld\n", iResult);
    return 0;
}


int ClientConnection::SendInt(const int & a) {
    printf("Sending int %d", a);
    iResult = 0;
    // Send an initial buffer
    int buf = htons(a);
    iResult = ::send(ConnectSocket(), reinterpret_cast<const char *>(&buf), (int) sizeof(int), 0);
    if (iResult == SOCKET_ERROR)
        return 1;

    //printf("Bytes Sent: %ld\n", iResult);
    printf("sent alright\n");
    return iResult;
}

int ClientConnection::GetInt() {
    printf("getting int...\n ");
    int a = 0;
    iResult = 0;
//    assert(ConnectSocket());
    while (iResult == 0)  {
        if (iResult == -1)
            return -1;
        Sleep(100);
    iResult = recv(ConnectSocket(), reinterpret_cast<char *>(&a), sizeof(int), 0);
    }
    a = ntohs(a);
    //assert(a != 0);
    printf("Got %d\n", a);
    return a;
}

std::string ClientConnection::GetString() {
    printf("Getting string\n");
    int size = 0;
    iResult = 0;
    while (iResult == 0) {
        Sleep(100);
        iResult = recv(ConnectSocket(), reinterpret_cast<char *>(&size),
                       sizeof(int), 0);
    }
    printf("HEREEEEE\n");
    if (iResult < 0) {
//        throw 1;
        std::cerr << "no connection, im in getstring 1";
    }
    size = ntohs(size);
    printf("size:: %d", size);
    std::vector<char> buf;
    buf.resize(size + 1);
    iResult = recv(ConnectSocket(), &(buf[0]), size, 0);
    std::string ans(&buf[0], size);
    if (iResult > 0) {
        std::cout << "Bytes received: " << iResult << "\n";
        std::cout << ans << "\n";
    }
    if (iResult < 0) {
//        throw 1;
        std::cerr << "no connection, im in getstring 2";
    }
    printf("got %s\n", ans.c_str());
    return ans;
}

int ClientConnection::CloseSocket() {
    // cleanup
    closesocket(ConnectSocket());
    WSACleanup();
    return 0;
}
