#include "Game.h"

void Game::connect_player(std::string name) {
    pool_connection[++players_amount] = std::make_unique<Player>(name);
}