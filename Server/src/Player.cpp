#include "Player.h"

void Player::add_tool(std::shared_ptr<Tool> &tool) {
    tools.push_back(tool);
}

Player::Player(const protocol &connection, std::string name)
    : name(std::move(name)), connection(connection){};

std::string Player::get_name() const {
    return name;
}

std::vector<std::shared_ptr<Tool>> &Player::get_tools() {
    return tools;
}
