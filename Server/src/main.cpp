#include <algorithm>
#include <chrono>  // std::chrono::system_clock
#include <iostream>
#include <random>  // std::default_random_engine
#include <utility>
#include "Game.h"

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();
#if 0
    game->connect_player("Oleg");
    game->connect_player("Fedor");

    game->info();
    std::shared_ptr<Button> button1 = std::make_shared<Button>("button1");
    std::shared_ptr<Button> button2 = std::make_shared<Button>("button2");
    std::shared_ptr<Button> button3 = std::make_shared<Button>("button3");
    std::shared_ptr<Button> button4 = std::make_shared<Button>("button4");
    std::shared_ptr<Button> button5 = std::make_shared<Button>("button5");
    std::shared_ptr<Button> button6 = std::make_shared<Button>("button6");
    std::shared_ptr<Button> button7 = std::make_shared<Button>("button7");
    std::shared_ptr<Button> button8 = std::make_shared<Button>("button8");
    std::shared_ptr<Slider> slider1_hor = std::make_shared<Slider>("slider1_hor");
    std::shared_ptr<Slider> slider2_hor = std::make_shared<Slider>("slider2_hor");
    std::shared_ptr<Slider> slider1_ver = std::make_shared<Slider>("slider1_ver", VERTICAL);
    std::shared_ptr<Slider> slider2_ver = std::make_shared<Slider>("slider2_ver", VERTICAL);
    game->add_tool_to_pool(button1);
    game->add_tool_to_pool(button2);
    game->add_tool_to_pool(button3);
    game->add_tool_to_pool(button4);
    game->add_tool_to_pool(slider1_hor);
    game->add_tool_to_pool(slider2_hor);
    game->add_tool_to_pool(slider1_ver);
    game->add_tool_to_pool(slider2_ver);
    game->add_tool_to_pool(button5);
    game->add_tool_to_pool(button6);
    game->add_tool_to_pool(button7);
    game->add_tool_to_pool(button8);
    game->assign_tools();
    game->info();
#endif

    std::vector<
        std::pair<std::shared_ptr<Tool>, std::vector<std::shared_ptr<Task>>>>
        task_storage;
    while (game->get_game_status() != END_OF_GAME) {
        if (game->get_game_status() == PLAYERS_ARE_READY) {
            unsigned seed =
                std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(task_storage.begin(), task_storage.end(),
                         std::default_random_engine(seed));

        }
    }
}
