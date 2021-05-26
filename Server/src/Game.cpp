#include "Game.h"
#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>  // for tests
#include <thread>
#include <utility>
#include <condition_variable>

Game::Game() : tl("C:\\Users\\Oleg\\Code-team\\Server\\tasks.json"){};
//    now point here your local file
//    when project is ready we can put here a relative path

int Game::get_players_amount() const {
    return players_amount;
}

void Game::connect_player(const protocol &connection, const std::string &name) {
    pool_connection.push_back(Player(connection, name));
    ++players_amount;
}

void Game::add_tool_to_pool(const json &tool_json) {
    if (tool_json["tool_type"] == "Button") {
        std::string tool_text = tool_json["tool_text"];
        std::shared_ptr<Button> button_ptr =
            std::make_shared<Button>(tool_text);
        tools_pool.push_back(button_ptr);
        for (const json &task : tool_json["tasks"]) {
            tasks_pool.push_back(Task(
                task["task_text"], Button(tool_text, task["tool_position"])));
        }
    } else if (tool_json["tool_type"] == "Slider") {
        std::string tool_text = tool_json["tool_text"];
        std::shared_ptr<Slider> slider_ptr =
            std::make_shared<Slider>(tool_text);
        tools_pool.push_back(slider_ptr);
        for (const json &task : tool_json["tasks"]) {
            int pos = task["tool_position"];
            std::string task_text = task["task_text"];
            tasks_pool.push_back(Task(task_text, Slider(tool_text, pos)));
        }
    } else {
        //  OTHER TOOLS
        assert(1);
    }
    InitialData::tool_count++;
}

GameStatus &Game::get_game_status() {
    return game_status;
}

// void Game::send_tools_to_player(int player_num) const {
// send_tools(pool_connection[player_num]->get_tools());
//}

void Game::connect_players() {
    std::vector<std::thread> threads;

    std::condition_variable cv;
    for (int i = 0; i < 8; ++i) {
        std::thread t([&]() {
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [&]() {
                return players_amount == i;
            });
            protocol client;
            cv.notify_all();
            std::string player_name = client.get_string();
            connect_player(client, player_name);
//            int tasks_amount = client.get_int();
//            if (tasks_amount != 0) {
//                Tool *tool = client.GetTool();
//            }
//            std::vector<Task> tasks_from_player;
//            for (; tasks_amount > 0; --tasks_amount) {
//                Tool *position = client.GetTool();
//                std::string task_text = client.get_string();
//
//            }
            for (int i = 0; i < 6; ++i) {
                add_tool_to_pool(tl.get_tool());
            }
        });
        threads.push_back(std::move(t));
    }
    for (auto &t : threads) {
        t.join();
    }
}

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
            if (task.get_tool()->tool_type() == "Button") {
                std::cout << "Button state: \n";
                const Button *button =
                    dynamic_cast<const Button *>(task.get_tool().get());
                if (button->get_state() == PUSHED) {
                    std::cout << "PUSHED\n";
                } else {
                    std::cout << "NOT PUSHED\n";
                }
            } else if (task.get_tool()->tool_type() == "Slider") {
                std::cout << "Slider state: \n";
                const Slider *slider =
                    dynamic_cast<const Slider *>(task.get_tool().get());
                std::cout << slider->get_state() << '\n';
            }
        }
    }
}

void Game::complete_active_task() {  // for tests
    for (const auto &task : tasks_pool) {
        if (task.active()) {
            if (task.get_tool()->tool_type() == "Button") {
                int id = task.get_tool()->id();
                dynamic_cast<Button *>(tools_pool[id].get())->change_state();
                break;
            }
            if (task.get_tool()->tool_type() == "Slider") {
                int id = task.get_tool()->id();
                dynamic_cast<Slider *>(tools_pool[id].get())
                    ->set_state(dynamic_cast<const Slider &>(*task.get_tool())
                                    .get_state());
                break;
            }
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