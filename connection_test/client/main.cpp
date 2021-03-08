#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>
#include <iostream>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

SOCKET& get_socket() {
    static auto sock = INVALID_SOCKET;
    return sock;
}

#pragma comment(lib, "Ws2_32.lib")

int initialize_winsock() {
    WSADATA wsaData;
    int iResult;

// Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    struct addrinfo *result = NULL,
            *ptr = NULL,
            hints{};

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
// Resolve the server address and port
    iResult = getaddrinfo("192.168.1.1", DEFAULT_PORT, &hints, &result);//Oleg`s IPv4 
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    auto ConnectSocket = INVALID_SOCKET;
    // Attempt to connect to the first address returned by
// the call to getaddrinfo
    ptr=result;

// Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                           ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

// Should really try the next address returned by getaddrinfo
// if the connect call failed
// But for this simple example we just free the resources
// returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        std::cout <<(WSAGetLastError()) << std::endl;
        return 1;
    }
    else {
        printf("Connected!\n");
    }
    get_socket() = ConnectSocket;
    return 0;
}

int send_info() {
    int recvbuflen = DEFAULT_BUFLEN;
    auto ConnectSocket = get_socket();
    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];

    int iResult;

// Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);
    return 0;
}

int shut_down() {
    auto ConnectSocket = get_socket();
    int iResult = 0;
    // shutdown the send half of the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}

int main() {
    initialize_winsock();
    std::string s;
    while(std::cin >> s) {
        if (s == "send")
            send_info();
        if (s == "stop") {
            shut_down();
            break;
        }
    }
    return 0;
}
