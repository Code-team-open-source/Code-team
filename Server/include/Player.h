#pragma once
#include <memory>
#include <vector>
#include "Tool.h"

class Player {
    std::string name;
    std::vector<std::shared_ptr<Tool>> tools;
    /*socket connection or smth like that*/

public:
    Player(std::string name);
    void add_tool(std::shared_ptr<Tool> tool);
};