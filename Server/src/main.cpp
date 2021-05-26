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
    protocol protocol1;
//    protocol1.send_string("ABOBA");
    for (int i = 0; i < 10; ++i) {
        Button b("gepa" + std::to_string(i));
        b.serialize(protocol1.s);
    }
protocol1.get_int();
//std::cout << protocol1.get_string() << "\n";
//    std::cout << protocol1.get_int();
#if 0
    tasklib tl("C:\\Users\\Oleg\\Code-team\\Server\\tasks.json");
//    now point here your local file
//    when project is ready we can put here a relative path
    tl.showlib();

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
