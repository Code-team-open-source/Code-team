#pragma once
#include <memory>
#include <mutex>
#include <queue>
#include <vector>
#include "ServerConnection.h"
#include "Tool.h"

class Player : public ServerConnection {
    std::string name;
    std::vector<std::shared_ptr<Tool>> tools;
    std::queue<std::string> queue_to_send;

public:
    mutable std::mutex player_mutex;
    void set_name(std::string);
    Player(const SOCKET &connection, std::string name);
    void add_tool(std::shared_ptr<Tool> &tool);
    std::string get_name() const;
    std::vector<std::shared_ptr<Tool>> &get_tools();

    void send_tools();
    void add_to_queue(std::string);
    void clear_data();
    std::string get_command();

    Player(Player &&pl) noexcept
        : ServerConnection(pl.clientSocket_),
          name(std::move(pl.name)),
          tools(std::move(pl.tools))
          {};
};
