#pragma once
#include <memory>
#include <vector>
#include "Tool.h"
#include "protocols.h"

class Player {
    std::string name;
    std::vector<std::shared_ptr<Tool>> tools;
    protocol connection;

public:
    Player(const protocol &connection, std::string name);
    void add_tool(std::shared_ptr<Tool> &tool);
    std::string get_name() const;
    std::vector<std::shared_ptr<Tool>> &get_tools();
};