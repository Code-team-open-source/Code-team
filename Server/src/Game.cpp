#include "Game.h"
#include <algorithm>
#include <cassert>
#include <condition_variable>
#include <ctime>
#include <iostream>  // for tests
#include <thread>
#include <utility>
#include <unistd.h>

Game::Game()
    : tl("tasks.json") {
}

void Game::accept(SOCKET s) {
    pool_connection.emplace_back(s, std::string("yet unknown player"));
    Player &player = pool_connection.back();
    player.set_name(player.GetString());
    player.SendString(std::to_string(pool_connection.size()));
    if (pool_connection.size() == 1) {
        std::thread t([&](){
            std::string str = pool_connection.back().GetString();
            if (str == "Game started") {
                std::unique_lock<std::mutex> lock(m);
                game_status = PLAYERS_ARE_READY;
            }
        });
        t.detach();
    }
    /*
    if( pool_connection.size() == InitialData::players_amount )
    {
        // starting the game

        for (auto &player : pool_connection)
        {
            // УТОЧНИТЬ ТУТ ЛОГИКУ!
            int crafted_tools = player.GetInt();
            auto tool = player.GetTool();

            std::vector<Task> tasks;
            for (int i = 0; i < crafted_tools; i++)
            {
                auto tool_pos = player.GetTool();
                std::string task = player.GetString();
                tasks.emplace_back(task, tool_pos.release());
            }
            if (tool) {
                tl.add_tool(*tool, tasks);
            }
        }
        */

}

//    now point here your local file
//    when project is ready we can put here a relative path

/*void Game::download_players_tools() {
    for (auto& player : pool_connection) {
        std::string checker = player.GetString();
        if (checker != "sending my tools") {
            std::cerr << "error in Game::download_players_tools. Have got: " <<
   checker;
        }
        int crafted_tools = player.GetInt();
*//*
        Tool *tool = nullptr;
        if (crafted_tools != 0)
            tool = player.GetTool(); // i just dont understand
*//*

        std::vector<Task> tasks;
        for (int i = 0; i < crafted_tools; i++) {
            auto tool_pos = player.GetTool();
            std::string task = player.GetString();
            tasks.emplace_back(task, *tool_pos);
        }
        if (tool != nullptr) {
            tl.add_tool(*tool, tasks);
        }
    }
}*/

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
        //        assert(1);
        std::cerr << "error in <<add tool to pool>>\n";
    }
    InitialData::tool_count++;
}

std::string Game::find_task(int owner) {
    for (auto &task : tasks_pool) {
        if (task.get_owner() == owner && task.active()) {
            return task.get_text();
        }
    }
    return "Error: player doesn't have a task";
}

GameStatus &Game::get_game_status() {
    return game_status;
}

void Game::round_prep() {
    clear_data();
    game_status = PLAYING;
    if (round++ != 1) {
        for (auto &pl : pool_connection) {
            pl.SendString("New round");
        }
        sec_for_task--;
    }
    else {
        for (auto &pl : pool_connection) {
            pl.SendString("Game started");
        }
    }
    for (int i = 0; i < 6 * InitialData::players_amount; ++i) {
        add_tool_to_pool(tl.get_tool());
    }
    assign_tools();


    for (int i = 0; i < InitialData::players_amount; ++i) {
        pool_connection[i].send_tools();
        pool_connection[i].SendInt(sec_for_task);
    }
    assign_initial_tasks();
}

void Game::start_round() {
    while(game_status != END_OF_GAME) {
        round_prep();
        std::vector<std::thread> threads;
        auto player_thread = [&](int player) {
            while (game_status != GameStatus::END_OF_GAME &&
                   game_status != GameStatus::END_OF_ROUND) {
                std::string from_player =
                    pool_connection[player].GetString(false);
                if (!from_player.empty()) {
                    if (from_player == "Tool changed") {
                        std::unique_lock lock(m);
                        commands.push("Tool changed");
                        int id = pool_connection[player].GetInt();
                        commands.push(std::to_string(id));
                        std::string position =
                            pool_connection[player].GetString();
                        commands.push(position);
                    }
                    if (from_player == "Task expired") {
                        std::unique_lock lock(m);
                        commands.push("Task expired");
                        commands.push(std::to_string(player));
                    }
                }
                Player &pl = pool_connection[player];
                std::unique_lock lock(pl.player_mutex);
                std::string command = pl.get_command();
                while (command != "None") {
                    if (command == "Send new task") {
                        pool_connection[player].SendString("New task");
                        pool_connection[player].SendString(find_task(player));
                    }
                    if (command == "End of round") {
                        pool_connection[player].SendString("End of round");
                    }
                    if (command == "End of game") {
                        pool_connection[player].SendString("End of game");
                    }
                    command = pl.get_command();
                }
            }
        };
        for (int player = 0; player < InitialData::players_amount; ++player) {
            std::thread t(player_thread, player);
            threads.push_back(std::move(t));
        }

        while (game_status != GameStatus::END_OF_GAME &&
               game_status != GameStatus::END_OF_ROUND) {
            std::unique_lock lock(m);
            while (!commands.empty()) {
                std::string command = commands.front();
                commands.pop();
                if (command == "Task expired") {
                    int player_id = std::stoi(commands.front());
                    commands.pop();
                    std::cout << "CHANGING TASK" << std::endl;
                    std::cout << "PREVIOUS TASK: " << find_task(player_id)
                              << std::endl;
                    task_expired(player_id);
                    std::cout << "CURRENT TASK: " << find_task(player_id)
                              << std::endl;
                }
                if (command == "Tool changed") {
                    int tool_id = std::stoi(commands.front());
                    commands.pop();
                    std::string pos = commands.front();
                    commands.pop();
                    std::cout << "TOOL CHANGED" << std::endl;
                    std::cout << "ID = " << tool_id << std::endl;
                    std::cout << "POSITION = " << pos << std::endl;
                    auto &tool = tools_pool[tool_id];
                    if (tool->tool_type() == "Button") {
                        ButtonState st;
                        if (pos == "not_pushed") {
                            st = ButtonState::NOT_PUSHED;
                        } else if (pos == "pushed") {
                            st = ButtonState::PUSHED;
                        } else {
                            std::cerr << "Invalid button state";
                            assert(0);
                        }
                        auto &button = dynamic_cast<Button &>(*tool);
                        if (st != button.get_state()) {
                            button.change_state();
                        }
                    } else if (tool->tool_type() == "Slider") {
                        int state = std::stoi(pos);
                        dynamic_cast<Slider &>(*tool).set_state(state);
                    }
                    int completed = change_completed_task();
                    std::cout << "COMPLETED TASK = " << completed << std::endl;
                    if (completed == -1) {
                        fails_left--;
                        if (fails_left == 0) {
                            game_status = END_OF_GAME;
                        }
                    } else {
                        std::cout << "TASKS LEFT = " << tasks_left << std::endl;
                        int owner = tasks_pool[completed].get_owner();
                        std::unique_lock lock_player(
                            pool_connection[owner].player_mutex);
                        pool_connection[owner].add_to_queue("Send new task");
                        tasks_left--;
                        if (tasks_left == 0) {
                            game_status = END_OF_ROUND;
                        }
                    }
                }
            }
        }
        if (game_status == END_OF_ROUND) {
            std::cout << "End of round\n";
        }
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

    }

    for (auto &pl : pool_connection) {
        pl.SendString("End of game");
    }
    std::cout << "End of game \n";
    sleep(10);

}

void Game::change_task(int task_owner_id) {
    std::unique_lock lock(pool_connection[task_owner_id].player_mutex);
    pool_connection[task_owner_id].add_to_queue("Send new task");
    lock.unlock();
    int prev_task = 0;
    for (auto &task : tasks_pool) {
        if (task.active() && task.get_owner() == task_owner_id) {
            task.change_status();
            break;
        }
        prev_task++;
    }
    std::srand(std::time(nullptr));
    int task_num = rand() % (tasks_pool.size());
    while (tasks_pool[task_num].active() || task_is_completed(task_num) ||
           task_num == prev_task) {
        task_num = rand() % (tasks_pool.size());
    }
    tasks_pool[task_num].change_status();
    tasks_pool[task_num].get_owner() = task_owner_id;
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

namespace {
bool tools_identical(Tool *first, Tool *second) {
    assert(first && second);

    if (first->tool_type() == "Button") {
        return dynamic_cast<Button &>(*first).get_state() ==
               dynamic_cast<Button &>(*second).get_state();
    }
    if (first->tool_type() == "Slider") {
        return dynamic_cast<Slider &>(*first).get_state() ==
               dynamic_cast<Slider &>(*second).get_state();
    }
    if (first->tool_type() == "CMD") {
        return dynamic_cast<CMD &>(*first).get_cmd_text() ==
               dynamic_cast<CMD &>(*second).get_cmd_text();
    }
    if (first->tool_type() == "Dial") {
        return dynamic_cast<Dial &>(*first).get_state() ==
               dynamic_cast<Dial &>(*second).get_state();
    }
    return 0;  // TODO i dont know if it should be here, fix pls (c) Fedya
}
}  // namespace

bool Game::task_is_completed(int task_num) const {
    Tool *correct_tool = tasks_pool[task_num].get_tool().get();
    Tool *actual_tool = tools_pool[correct_tool->id()].get();
    return tools_identical(correct_tool, actual_tool);
}

void Game::assign_tools() {
    if (static_cast<int>(tools_pool.size()) !=
        InitialData::players_amount * InitialData::blocks_per_user) {
        std::cerr << "error in assign tools";
    }
    int player_id = 0;
    for (auto &tool : tools_pool) {
        pool_connection[player_id].add_tool(tool);
        player_id = (player_id + 1) % InitialData::players_amount;
    }
}

void Game::assign_initial_tasks() {
    for (int player_id = 0; player_id < InitialData::players_amount; ++player_id) {
        change_task(player_id);
    }
}

void Game::clear_data() {
    for (auto &pl : pool_connection) {
        pl.clear_data();
    }
    tools_pool.clear();
    tasks_pool.clear();
    InitialData::tool_count = 0;
    tasks_left = InitialData::tasks_to_be_done_in_round;
    fails_left = InitialData::amount_of_fails_allowed;
}

int Game::change_completed_task() {
    for (unsigned int task_num = 0; task_num < tasks_pool.size(); ++task_num) {
        if (tasks_pool[task_num].active() && task_is_completed(task_num)) {
            tasks_left--;
            if (tasks_left == 0) {
                game_status = END_OF_ROUND;
            }
            change_task(tasks_pool[task_num].get_owner());
            return task_num;
        }
    }
    return -1;
}
