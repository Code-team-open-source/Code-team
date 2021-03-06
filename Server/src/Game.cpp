#include "Game.h"
#include <algorithm>
#include <ctime>
#include <cassert>
#include <iostream>  // for tests
#include <utility>

int Game::get_players_amount() const {
    return players_amount;
}

void Game::connect_player(const std::string &name) {
    pool_connection.push_back(std::make_unique<Player>(name));
    ++players_amount;
}

void Game::add_tool_to_pool(
    const std::pair<std::shared_ptr<Tool>, std::vector<std::shared_ptr<Task>>>
        &tool) {
    tools_pool.push_back(tool.first);
    for (const auto &task : tool.second) {
        tasks_pool.push_back(task);
    }
}

GameStatus &Game::get_game_status() {
    return game_status;
}

void Game::send_tools_to_player(int player_num) const {
    // send_tools(pool_connection[player_num]->get_tools());
}

void Game::change_task(int task_owner_id) {
    for (auto &task : tasks_pool) {
        if (task->active() && task->get_owner() == task_owner_id) {
            task->change_status();
            break;
        }
    }
    std::srand(std::time(nullptr));
    int task_num = rand() % (tasks_pool.size());
    while (tasks_pool[task_num]->active()) {
        task_num = rand() % (tasks_pool.size());
    }
    tasks_pool[task_num]->change_status();
    tasks_pool[task_num]->get_owner() = task_owner_id;
    send_task(task_owner_id);
}

void Game::task_expired() {
    tasks_left--;
}

// for tests
void Game::info() {
    std::cout << "Tools at all: ";
    for (auto tool : tools_pool) {
        std::cout << tool->get_text() << '\n';
    }
    for (auto &player : pool_connection) {
        std::cout << ' ' << player->get_name() << '\n';
        auto vec = player->get_tools();
        for (auto tool : vec) {
            std::cout << tool->get_text() << "  tool id = " << tool->id()
                      << '\n';
        }
    }
}

void Game::assign_tools() {
    assert(static_cast<int>(tools_pool.size()) ==
           players_amount * InitialData::blocks_per_user);
    int player_id = 0;
    for (auto &tool : tools_pool) {
        pool_connection[player_id]->add_tool(tool);
        player_id = (player_id + 1) % players_amount;
    }
}