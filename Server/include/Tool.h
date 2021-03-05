#pragma once
#include "InitialData.h"
#include <string>

struct Position {
    int left_upper_corner;
    int right_lower_corner;
};

class Tool {
private:
    std::string tool_text;
    const int size_on_screen = 1;
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
    Tool(std::string text, int size);
    int get_size();
    void set_position(Position position_);
    Position get_position();
    std::string get_text();
    virtual ~Tool() = default;
};

enum ButtonState {
    PUSHED,
    NOT_PUSHED,
};

class Button : public Tool {
private:
    ButtonState current_state;

public:
    Button(std::string text);
    ButtonState get_state();
    void change_state();
};

enum Orientation {
    VERTICAL,
    HORIZONTAL,
};

class Slider : public Tool {
private:
    int available_positions = InitialData::slider_positions;
    int current_state = 1;
    Orientation orientation;

public:
    Slider(std::string text, Orientation orientation_);
    int get_state();
    void set_new_position(int new_position);
    Orientation get_orientation() const ;
};

