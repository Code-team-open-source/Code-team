#include <unistd.h>
#include <algorithm>
#include <cassert>
#include <chrono>  // std::chrono::system_clock
#include <iostream>
#include <random>  // std::default_random_engine
#include <utility>
#include "Game.h"
#include "protocols.h"

int InitialData::tool_count = 0;

int main() {

    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->connect_players();
    game->info();
    std::cout << "====================\n";
    game->assign_tools();
    game->info();
    game->show_active_tasks();
    game->assign_initial_tasks();
    game->show_active_tasks();
    game->complete_active_task();
    game->change_completed_tasks();
    game->show_active_tasks();


}
