#include "Game.h"
#include <algorithm>

void Game::connect_player(std::string name) {
    pool_connection[++players_amount] = std::make_unique<Player>(name);
}

namespace {
struct ToolField {
    int capacity_left = 6;
    bool field[6] = {true, true, true, true, true, true};  // if block is empty
};
}  // namespace

void Game::assign_tools() {
    std::vector<ToolField> players_field(players_amount);
    // how many tool blocks left
    sort(tools_pool.begin(), tools_pool.end(),
         [](std::shared_ptr<Tool> a, std::shared_ptr<Tool> b) {
             return a->get_size() > b->get_size();
         });
    int player_id = 0;
    for (auto &tool : tools_pool) {
        bool found_player = false;
        while (!found_player) {
            if (players_field[player_id].capacity_left >= tool->get_size()) {
                if (const auto& b = dynamic_cast<const Button *>(&(*tool)); b)



                    found_player = true;
                pool_connection[player_id + 1]->add_tool(tool);
            }
            player_id = (player_id + 1) % players_amount;
        }
    }
}