#pragma once
#include "InitialData.h"
#include <string>

struct Position {
    int left_upper_corner;
    int right_lower_corner;
};

class Tool {
    std::string tool_text;
    int size_on_screen;
    /* size_on_screen is measured in blocks (1-6):
            *****************
            *       *       *
            *   1   *   2   *
            *       *       *
            *****************
            *       *       *
            *   3   *   4   *
            *       *       *
            *****************
            *       *       *
            *   5   *   6   *
            *       *       *
            *****************
     */
    Position position;

public:
    Position get_position();
    std::string get_text();
};

enum ButtonState {
    PUSHED,
    NOT_PUSHED,
};

class Button : Tool {
    ButtonState current_state;

public:
    ButtonState get_state();
    void change_state();
};

class Slider : Tool {
    int available_positions = InitialData::slider_positions;
    int current_state = 1;

public:
    int get_state();
    void set_new_position(int new_position);
};

