#include "Game.h"
#include <algorithm>
#include <iostream>  // for tests
#include <cassert>

int Game::get_players_amount() const {
    return players_amount;
}

void Game::connect_player(const std::string &name) {
    pool_connection[++players_amount] = std::make_unique<Player>(name);
}

void Game::add_tool_to_pool(std::shared_ptr<Tool> tool) {
    tools_pool.push_back(tool);
}

GameStatus Game::get_game_status() const {
    return game_status;
}


// for tests
void Game::info() {
    std::cout << "Tools at all: ";
    for (auto tool : tools_pool) {
        std::cout << tool->get_text() << '\n';
    }
    for (auto &player : pool_connection) {
        std::cout << player.first << ' ' << player.second->get_name() << '\n';
        auto vec = player.second->get_tools();
        for (auto tool : vec) {
            std::cout << tool->get_text() <<  "  tool id = " << tool->id() << '\n';
        }
    }
}

void Game::assign_tools() {
    assert(static_cast<int>(tools_pool.size()) == players_amount * 6);
    int player_id = 0;
    for (auto &tool : tools_pool) {
        pool_connection[player_id + 1]->add_tool(tool);
        player_id = (player_id + 1) % players_amount;
    }
}