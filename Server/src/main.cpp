#include <algorithm>
#include <cassert>
#include <chrono>  // std::chrono::system_clock
#include <iostream>
#include <random>  // std::default_random_engine
#include <utility>
#include "ServerConnection.h"
#include "Server.h"
#include "Game.h"

int InitialData::tool_count = 0;

int main()
try
{
    CodeTeamServer server;
    Game game; // game for 2 players

    server.setSink(&game);
    server.listen(game.accept_players, game.m);
    std::cout << "starting game\n";
    game.start_round();
    return 0;
}
catch (std::exception &e)
{
    std::cout << "Error "  << e.what() << std::endl;
    return -1000;
}
catch (int rc)
{
    std::cout << "Error "  << rc << std::endl;
    return rc;
}
catch (...)
{
    std::cout << "Unknown error!" << std::endl;
    return -100;
}
