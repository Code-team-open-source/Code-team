#include "Tool.h"
#include <cassert>

Tool::Tool(std::string text, int size)
    : tool_text(std::move(text)), size_on_screen(size){};

void Tool::set_position(Position position_) {
    position = position_;
}

Position Tool::get_position() {
    return position;
}
std::string Tool::get_text() {
    return tool_text;
}

int Tool::get_size() {
    return size_on_screen;
}

Button::Button(std::string text) : Tool(text, 1){};

ButtonState Button::get_state() {
    return current_state;
}
void Button::change_state() {
    current_state = (current_state == PUSHED ? NOT_PUSHED : PUSHED);
}

Slider::Slider(std::string text, Orientation orientation_ = HORIZONTAL)
    : Tool(text, 2), orientation(orientation_){};

int Slider::get_state() {
    return current_state;
}
void Slider::set_new_position(int new_position) {
    assert(new_position > 0 && new_position <= available_positions);
    current_state = new_position;
}