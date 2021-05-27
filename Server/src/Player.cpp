#include "Player.h"

void Player::add_tool(std::shared_ptr<Tool> &tool) {
    tools.push_back(tool);
}

Player::Player(const SOCKET &connection, std::string name)
    : name(std::move(name)), sock(connection){};

std::string Player::get_name() const {
    return name;
}

std::vector<std::shared_ptr<Tool>> &Player::get_tools() {
    return tools;
}

void Player::send_tools() {
    for (const auto &tool : tools) {
        ServerConnection::SendTool(*tool, sock);
    }
}

void Player::add_to_queue(std::string str) {
    queue_to_send.push(std::move(str));
}

void Player::clear_data() {
    while(!queue_to_send.empty()) {
        queue_to_send.pop();
    }
    tools.clear();
}

std::string Player::get_command() {
    if (queue_to_send.empty()) {
        return "None";
    }
    std::string str = queue_to_send.front();
    queue_to_send.pop();
    return str;
}