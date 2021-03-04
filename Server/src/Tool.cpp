#include "Tool.h"

Position Tool::get_position() {
    return position;
}
std::string Tool::get_text() {
    return tool_text;
}

ButtonState Button::get_state() {
    return state;
}
void Button::change_state() {
    state = (state == PUSHED ? NOT_PUSHED : PUSHED);
}