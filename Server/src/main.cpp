#include <unistd.h>
#include <algorithm>
#include <cassert>
#include <chrono>  // std::chrono::system_clock
#include <iostream>
#include <random>  // std::default_random_engine
#include <utility>
#include "Game.h"
#include "ServerConnection.h"

int InitialData::tool_count = 0;

int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->connect_players();
}