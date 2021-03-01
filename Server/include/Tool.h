#pragma once
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
};

enum ButtonState {
    PUSHED,
    NOT_PUSHED,
};

class Button : Tool {
    ButtonState state;
};
