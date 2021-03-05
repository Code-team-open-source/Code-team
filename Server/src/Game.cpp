#include "Game.h"
#include <algorithm>

void Game::connect_player(std::string name) {
    pool_connection[++players_amount] = std::make_unique<Player>(name);
}

namespace {
struct ToolField {
    int capacity_left = 6;
    bool field[6] = {true, true, true, true, true, true};  // if block is empty
};
}  // namespace

void Game::assign_tools() {
    std::vector<ToolField> players_field(players_amount);
    // how many tool blocks left
    sort(tools_pool.begin(), tools_pool.end(),
         [](std::shared_ptr<Tool> a, std::shared_ptr<Tool> b) {
             return a->get_size() > b->get_size();
         });
    int player_id = 0;
    for (auto tool : tools_pool) {
        bool found_player = false;
        while (!found_player) {
            if (players_field[player_id].capacity_left >= tool->get_size()) {
                if (const auto &b = dynamic_cast<const Button *>(tool.get());
                    b) {
                    for (int block = 0; block < 6; ++block) {
                        if (players_field[player_id].field[block]) {
                            found_player = true;
                            players_field[player_id].field[block] = false;
                            tool->set_position({block, block});
                        }
                    }
                }
                if (const auto &s = dynamic_cast<const Slider *>(tool.get());
                    s) {
                    const Slider *slider =
                        dynamic_cast<const Slider *>(tool.get());
                    if (slider->get_orientation() == HORIZONTAL) {
                        for (int first_block = 1; first_block <= 5;
                             first_block += 2) {
                            if (players_field[player_id].field[first_block] &&
                                players_field[player_id]
                                    .field[first_block + 1]) {
                                found_player = true;
                                players_field[player_id].field[first_block] =
                                    false;
                                players_field[player_id]
                                    .field[first_block + 1] = false;
                                tool->set_position(
                                    {first_block, first_block + 1});
                                break;
                            }
                        }
                    } else {
                        for (int block = 1; block <= 4; ++block) {
                            if (players_field[player_id].field[block] &&
                                players_field[player_id].field[block + 2]) {
                                found_player = true;
                                players_field[player_id].field[block] = false;
                                players_field[player_id].field[block + 2] =
                                    false;
                                tool->set_position({block, block + 2});
                                break;
                            }
                        }
                    }
                }
                if (found_player) {
                    pool_connection[player_id + 1]->add_tool(tool);
                }
            }
            player_id = (player_id + 1) % players_amount;
        }
    }
}