#pragma once
#include "InitialData.h"
#include "Player.h"
#include <unordered_map>
#include <vector>
#include <memory>

enum GameStatus {
    WAITING_IN_LOBBY,
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

public:
    void connect_player(std::string name);
    void assign_tools();
};