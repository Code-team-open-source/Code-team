#include "Game.h"
#include <iostream>

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();
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
    return 0;
}
