#include "Tool.h"
#include <cassert>

Position Tool::get_position() {
    return position;
}
std::string Tool::get_text() {
    return tool_text;
}

ButtonState Button::get_state() {
    return current_state;
}
void Button::change_state() {
    current_state = (current_state == PUSHED ? NOT_PUSHED : PUSHED);
}

int Slider::get_state() {
    return current_state;
}
void Slider::set_new_position(int new_position) {
    assert(new_position > 0 && new_position < available_positions);
    current_state = new_position;
}