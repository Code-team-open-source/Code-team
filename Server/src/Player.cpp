#include "Player.h"

void Player::add_tool(std::shared_ptr<Tool> tool) {
    tools.push_back(tool);
}

Player::Player(std::string name) : name(std::move(name)){
            /*generate socket connection*/
      };

