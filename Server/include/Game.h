#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include <queue>
#include "InitialData.h"
#include "Task.h"
#include "nlohmann/json.hpp"
#include "tasklib.h"
#include "Server.h"

using json = nlohmann::json;

enum GameStatus {
    WAITING_IN_LOBBY,
    PLAYERS_ARE_READY,
    PLAYING,
    END_OF_ROUND,
    END_OF_GAME,
};

class Game : public IListenerSink
{
    GameStatus game_status = WAITING_IN_LOBBY;
    int round = 1;
    int tasks_left = InitialData::tasks_to_be_done_in_round;
    int fails_left = InitialData::amount_of_fails_allowed;
    int sec_for_task = InitialData::time_for_one_task;

    const unsigned short players_amount;
    std::vector<Player> pool_connection;
    std::vector<std::shared_ptr<Tool>> tools_pool;
    std::vector<Task> tasks_pool;
    mutable std::mutex m;
    tasklib tl;
    std::queue<std::string> commands;

    std::string find_task(int);
public:

    void round_prep();
    void start_round();
    void assign_tools();
    void add_tool_to_pool(const json &tool);
    GameStatus &get_game_status();
    void task_expired(int task_owner_id);
    void change_task(int task_owner_id);
    void info();  // for tests
    void assign_initial_tasks();
    bool task_is_completed(int task_num) const;
    void show_active_tasks() const;  // for tests
    int change_completed_task();
    void complete_active_task();  // for tests
    void clear_data();

    Game( unsigned short num_of_players);

    void accept(SOCKET s) override;
};
