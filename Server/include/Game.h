#pragma once
#include <memory>
#include <vector>
#include "InitialData.h"
#include "Task.h"

enum GameStatus {
    WAITING_IN_LOBBY,
    PLAYERS_ARE_READY,
    PLAYING,
    END_OF_ROUND,
    END_OF_GAME,
};

class Game {
    GameStatus game_status = WAITING_IN_LOBBY;
    int round = 1;
    int tasks_left = InitialData::tasks_to_be_done_in_round;
    int fails_left = InitialData::amount_of_fails_allowed;

    int players_amount = 0;
    std::vector<std::unique_ptr<Player>> pool_connection;
    std::vector<std::shared_ptr<Tool>> tools_pool;
    std::vector<std::shared_ptr<Task>> tasks_pool;

public:
    int get_players_amount() const ;
    void connect_player(const std::string &name);
    void assign_tools();
    void add_tool_to_pool(
        const std::pair<std::shared_ptr<Tool>,
                        std::vector<std::shared_ptr<Task>>> &tool);
    GameStatus &get_game_status();
    void send_tools_to_player(int player_num) const;
    void task_expired();
    void change_task(int task_owner_id);
    void info();
};