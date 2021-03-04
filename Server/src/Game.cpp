#include "Game.h"
#include <algorithm>

void Game::connect_player(std::string name) {
    pool_connection[++players_amount] = std::make_unique<Player>(name);
}

void Game::assign_tools() {
    std::vector<int> capacity_left(players_amount, 6);
    // how many tool blocks left
    sort(tools_pool.begin(), tools_pool.end(),
         [](Tool a, Tool b) { return a.get_size() > b.get_size(); });
    int player_id = 0;
    for (auto tool : tools_pool) {
        bool found_player = false;
        while (!found_player) {
            if (capacity_left[player_id] >= tool.get_size()) {
                found_player = true;
                pool_connection[player_id + 1]->add_tool(tool);
                capacity_left[player_id] -= tool.get_size();
            }
            player_id = (player_id + 1) % players_amount;
        }
    }
}