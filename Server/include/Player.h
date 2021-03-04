#pragma once
#include "Tool.h"
#include <vector>

class Player {
    std::string name;
    std::vector<Tool> tools;
    /*socket connection or smth like that*/

public:
    Player(std::string name);
};