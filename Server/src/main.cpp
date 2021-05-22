#include <algorithm>
#include <cassert>
#include <chrono>  // std::chrono::system_clock
#include <iostream>
#include <random>  // std::default_random_engine
#include <utility>
#include "Game.h"
#include "tasklib.h"
#include <unistd.h>
#include "protocols.h"

int InitialData::tool_count = 0;

int main() {
    protocol protocol1;
    std::string str = protocol1.get_string();
    for (int i = 1; i < 11; ++i) {
//        Button button("test button");
        protocol1.send_int(i);
    }

#if 0
    tasklib tl("C:\\Users\\Oleg\\Code-team\\Server\\tasks.json");
//    now point here your local file
//    when project is ready we can put here a relative path
    tl.showlib();

    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->info();
    game->add_tool_to_pool(tl.get_tool());
    game->add_tool_to_pool(tl.get_tool());

    game->info();



    //    protocol protocol1;
//    protocol1.send_string("5 1234\n");

//    int out = protocol1.get_int();
//    std::cout << out << '\n';

//    std::string str = protocol1.get_string();
//    std::cout << str << '\n';


//    protocol protocol2;
//    protocol2.send_string("Second Connection\n");


    std::unique_ptr<Game> game = std::make_unique<Game>();
//    game->connect_player(protocol1, );
    game->connect_player("Fedor");
    game->info();
    for (int i = 0; i < 12; ++i) {
        std::string t = "Button" + std::to_string(i);
        std::string task_text = "Task" + std::to_string(i);
        Button button(t);
        Button correct1 = button;
        Button correct2 = button;
        correct2.change_state();
        game->add_tool_to_pool(
            {button, {Task(task_text, correct1), Task(task_text, correct2)}});
    }
    game->assign_tools();
    game->info();
    game->show_active_tasks();
    game->assign_initial_tasks();
    game->show_active_tasks();
    game->complete_active_task();
    game->change_completed_tasks();
    game->show_active_tasks();

    std::vector<
        std::pair<Tool, std::vector<Task>>>
        task_storage;
    /* connecting players */
    if (game->get_game_status() == PLAYERS_ARE_READY) {
        unsigned seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(task_storage.begin(), task_storage.end(),
                     std::default_random_engine(seed));
        for (int tool_num = 0; tool_num < InitialData::blocks_per_user *
                                              game->get_players_amount();
             ++tool_num) {
            assert(tool_num < static_cast<int>(task_storage.size()));
            game->add_tool_to_pool(task_storage[tool_num]);
        }
        game->assign_tools();
        for (int player = 0; player < game->get_players_amount(); ++player) {
            game->send_tools_to_player(player);
        }
        game->get_game_status() = GameStatus::PLAYING;
    }
    while (game->get_game_status() != END_OF_GAME) {
        for (int player = 0; player < game->get_players_amount(); ++player) {
            if (get_message() == "Task expired") {
                game->task_expired();
                game-
            }
        }
    }
#endif
}
