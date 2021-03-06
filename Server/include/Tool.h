#pragma once
#include "InitialData.h"
#include <string>

class Tool {
private:
    std::string tool_text;
    int tool_id;
public:
    Tool(std::string text);
    std::string get_text();
    int id() const ;
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
    Orientation orientation = HORIZONTAL;

public:
    Slider(std::string text);
    Slider(std::string text, Orientation orientation_);
    int get_state();
    void set_new_position(int new_position);
    Orientation get_orientation() const ;
};

