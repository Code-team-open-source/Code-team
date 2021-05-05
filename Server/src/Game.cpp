#include "Game.h"
#include <algorithm>
#include <ctime>
#include <cassert>
#include <iostream>  // for tests
#include <utility>

int Game::get_players_amount() const {
    return players_amount;
}

void Game::connect_player(const protocol &connection, const std::string &name) {
    pool_connection.push_back(Player(connection, name));
    ++players_amount;
}

void Game::add_tool_to_pool(
    const std::pair<const Tool &, std::vector<Task>>
        &tool) {
    const auto *b = dynamic_cast<const Button *>(&tool.first);
    if (b != nullptr) {
        tools_pool.push_back(std::make_shared<Button>(*b));
    }
    const auto *s = dynamic_cast<const Slider *>(&tool.first);
    if (s != nullptr) {
        tools_pool.push_back(std::make_shared<Slider>(*s));
    }

//    FOR OTHER TOOLS

    for (const auto &task : tool.second) {
        tasks_pool.push_back(task);
    }
}

GameStatus &Game::get_game_status() {
    return game_status;
}

//void Game::send_tools_to_player(int player_num) const {
    // send_tools(pool_connection[player_num]->get_tools());
//}

void Game::change_task(int task_owner_id) {
    for (auto &task : tasks_pool) {
        if (task.active() && task.get_owner() == task_owner_id) {
            task.change_status();
            break;
        }
    }
    std::srand(std::time(nullptr));
    int task_num = rand() % (tasks_pool.size());
    while (tasks_pool[task_num].active() || task_is_completed(task_num)) {
        task_num = rand() % (tasks_pool.size());
    }
    tasks_pool[task_num].change_status();
    tasks_pool[task_num].get_owner() = task_owner_id;
//    send_task(task_owner_id);
}

void Game::task_expired(int task_owner_id) {
    fails_left--;
    if (fails_left == 0) {
        game_status = END_OF_GAME;
        return;
    }
    change_task(task_owner_id);
}

// for tests
void Game::info() {
    std::cout << "Tools at all: ";
    for (const auto &tool : tools_pool) {
        std::cout << tool->get_text() << '\n';
    }
    for (auto &player : pool_connection) {
        std::cout << ' ' << player.get_name() << '\n';
        auto vec = player.get_tools();
        for (const auto &tool : vec) {
            std::cout << tool->get_text() << "  tool id = " << tool->id()
                      << '\n';
        }
    }
}

void Game::show_active_tasks() const {
    std::cout << "ACTIVE TASKS: \n";
    for (const Task &task : tasks_pool) {
        if (task.active()) {
            std::cout << task.get_text() << '\n';
            std::cout << "Button state: \n";
            const Button *button = dynamic_cast<const Button *>(task.get_tool().get());
            if (button->get_state() == PUSHED) {
                std::cout << "PUSHED\n";
            } else {
                std::cout << "NOT PUSHED\n";
            }

        }
    }
}

void Game::complete_active_task() { // for tests
    for (const auto &task :tasks_pool) {
        if (task.active()) {
            int id = task.get_tool()->id();
            dynamic_cast<Button *>(tools_pool[id].get())->change_state();
            break;
        }
    }
}


bool Game::task_is_completed(int task_num) const {
    Tool *correct_tool = tasks_pool[task_num].get_tool().get();
    Tool *actual_tool = tools_pool[correct_tool->id()].get();
    return correct_tool->operator==(actual_tool);
}

void Game::assign_tools() {
    assert(static_cast<int>(tools_pool.size()) ==
           players_amount * InitialData::blocks_per_user);
    int player_id = 0;
    for (auto &tool : tools_pool) {
        pool_connection[player_id].add_tool(tool);
        player_id = (player_id + 1) % players_amount;
    }
}

void Game::assign_initial_tasks() {
    for (int player_id = 0; player_id < players_amount; ++player_id) {
        change_task(player_id);
    }
}

void Game::change_completed_tasks() {
    for (unsigned int task_num = 0; task_num < tasks_pool.size(); ++task_num) {
        if (tasks_pool[task_num].active() && task_is_completed(task_num)) {
            tasks_left--;
            if (tasks_left == 0) {
                game_status = END_OF_ROUND;
                return;
            }
            change_task(tasks_pool[task_num].get_owner());
        }
    }
}