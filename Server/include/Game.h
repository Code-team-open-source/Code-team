#pragma once
#include "InitialData.h"
#include "Player.h"
#include <unordered_map>
#include <vector>
#include <memory>

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
    std::unordered_map<int, std::unique_ptr<Player>> pool_connection;
    std::vector<std::shared_ptr<Tool>> tools_pool;
    std::vector<Task> active_tasks;
    std::vector<Task> all_tasks; // without active tasks

public:
    int get_players_amount() const;
    void connect_player(const std::string &name);
    void assign_tools();
    void add_tool_to_pool(std::shared_ptr<Tool>);
    GameStatus get_game_status() const ;
    void info();
};