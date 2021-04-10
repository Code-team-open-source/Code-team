#include "Tool.h"
#include <cassert>
#include <iostream> // for tests


Tool::Tool(std::string text)
    : tool_text(std::move(text)), tool_id(InitialData::tool_count) {
    InitialData::tool_count++;
};

std::string Tool::get_text() {
    return tool_text;
}

int Tool::id() const {
    return tool_id;
}

Button::Button(std::string text) : Tool(text){};

ButtonState Button::get_state() const {
    return current_state;
}
void Button::change_state() {
    current_state = (current_state == PUSHED ? NOT_PUSHED : PUSHED);
}

bool Button::operator==(Tool *other) const {
    const auto *button = dynamic_cast<const Button *>(other);
    assert(button);
    return current_state == button->current_state;
}

Slider::Slider(std::string text) : Tool(text){};

Slider::Slider(std::string text, Orientation orientation_)
    : Tool(text), orientation(orientation_){};

int Slider::get_state() {
    return current_state;
}
void Slider::set_new_position(int new_position) {
    assert(new_position > 0 && new_position <= available_positions);
    current_state = new_position;
}

Orientation Slider::get_orientation() const {
    return orientation;
}

bool Slider::operator==(Tool *other) const {
    const auto *slider = dynamic_cast<const Slider *>(other);
    assert(slider);
    return current_state == slider->current_state;
}