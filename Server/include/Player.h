#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include <queue>
#include "Tool.h"
#include "protocols.h"

class Player {
    std::string name;
    std::vector<std::shared_ptr<Tool>> tools;
    std::queue<std::string> queue_to_send;

public:
    mutable std::mutex player_mutex;

    SOCKET sock;
    Player(const SOCKET& connection, std::string name);
    void add_tool(std::shared_ptr<Tool> &tool);
    std::string get_name() const;
    std::vector<std::shared_ptr<Tool>> &get_tools();
    void send_tools();
    void add_to_queue(std::string);
};