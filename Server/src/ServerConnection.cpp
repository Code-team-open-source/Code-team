//
// Created by Fedya on 19.04.2021.
//
#include "ServerConnection.h"
#include <cassert>
#include <memory>
#include <vector>
#include <memory>
#include "Tool.h"

std::string ServerConnection::GetString(bool wait) const {
    int size = 0;
    auto iResult = 0;
    fd_set s_set = {1, {clientSocket_}};
    timeval timeout = {0, 0};
    if (!wait) {
        bool aaaaaaaaaaaa = select(0, &s_set, 0, 0, &timeout);
        if (aaaaaaaaaaaa)
            iResult = recv(clientSocket_, reinterpret_cast<char *>(&size),
                           sizeof(int), 0);
        else
            return "";
    }
    else {
        iResult = recv(clientSocket_, reinterpret_cast<char *>(&size),
                       sizeof(int), 0);
    }
    size = ntohs(size);
    std::vector<char> buf;
    buf.resize(size + 1);
    if (iResult > 0) {
        iResult = recv(clientSocket_, &(buf[0]), size, 0);
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
//    std::cout << "Got " << ans << "\n";
    return ans;
}

int ServerConnection::GetInt() const{
    SOCKET ClientSocket = clientSocket_;
//    std::cout << "Getting int\n";
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
//    std::cout << "Got " << num << "\n";
    return num;
}

int ServerConnection::SendString(const std::string &str) const {
    SOCKET ClientSocket = clientSocket_;
//    std::cout << "Sending string: " << str << "\n";
    auto iResult = 0;
    // Send an initial buffer
    int size = str.size();
    size = htons(size);
    iResult = ::send(ClientSocket, reinterpret_cast<const char *>(&size),
                     (int)sizeof(int), 0);
    if (iResult == SOCKET_ERROR)
        return 1;
    iResult = ::send(clientSocket_, str.c_str(), str.size(), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        return 1;
    }
//    std::cout << "sent alright\n";
    // printf("Bytes Sent: %ld\n", iResult);
    return 0;
}

int ServerConnection::SendInt(const int number) const {
    SOCKET ClientSocket = clientSocket_;

//    std::cout << "sending int: " << number << "\n";
    int temnumber = number;
//    std::cout << " SendInt: " << number << "\n";
    temnumber = htons(temnumber);
    send(ClientSocket, reinterpret_cast<const char *>(&temnumber), sizeof(int),
         0);
//    std::cout << "Sent alright\n";
    return 0;
}
ServerConnection::ServerConnection(SOCKET clientSocket) : clientSocket_(clientSocket)
{
}

std::unique_ptr<Tool> ServerConnection::GetTool() const
{
    SOCKET Clsock = clientSocket_;
    std::string str = ServerConnection::GetString(Clsock);

    std::unique_ptr<Tool> t;

    if (str == "Button") {
        t = std::make_unique<Button>( "" );
    }
    if (str == "Slider") {
        t = std::make_unique<Slider>( "" );
    }
    if (str == "Dial") {
        t = std::make_unique<Dial>( "" );
    }
    if (str == "CMD") {
        t = std::make_unique<CMD>( "" );
    }

    if (t == nullptr) {
        throw 6;
    }
    ServerConnection temp = *this;
    t->deserialize(temp);
    return t;
}

void ServerConnection::SendTool(const Tool &t) const
{
    t.serialize(*this);
}
