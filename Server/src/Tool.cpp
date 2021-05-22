#include "Tool.h"
#include <cassert>
#include <iostream>  // for tests
#include "ServerConnection.h"

Tool::Tool(std::string text)
    : tool_text(std::move(text)), tool_id(InitialData::tool_count) {
};

std::string Tool::get_text() const {
    return tool_text;
}

int Tool::id() const {
    return tool_id;
}

Button::Button(std::string text) : Tool(std::move(text)){};

Button::Button(std::string text, ButtonState bs)
    : Tool(std::move(text)), current_state(bs) {
}

ButtonState Button::get_state() const {
    return current_state;
}
void Button::change_state() {
    current_state = (current_state == PUSHED ? NOT_PUSHED : PUSHED);
}

std::string Button::tool_type() const {
    return "Button";
}

bool Button::operator==(Tool *other) const {
    const auto *button = dynamic_cast<const Button *>(other);
    assert(button);
    return current_state == button->current_state;
}

Slider::Slider(std::string text) : Tool(std::move(text)){};
Slider::Slider(std::string text, int pos)
    : Tool(std::move(text)), current_state(pos) {
}

int Slider::get_state() const {
    return current_state;
}

void Slider::set_state(int pos) {
    current_state = pos;
}

void Slider::set_new_position(int new_position) {
    assert(new_position > 0 && new_position <= available_positions);
    current_state = new_position;
}

std::string Slider::tool_type() const {
    return "Slider";
}

bool Slider::operator==(Tool *other) const {
    const auto *slider = dynamic_cast<const Slider *>(other);
    assert(slider);
    return current_state == slider->current_state;
}

// new
// may be should be moved
// Oleg
// TODO
void Tool::serialize(ServerConnection s) {
    s.SendString(tool_text);
    std::cout << "tool_text=" << tool_text << std::endl;
    s.SendInt(tool_id);
    std::cout << "tool_id=" << tool_id << std::endl;
}
void Tool::deserialize(ServerConnection s) {
    std::string check = s.GetString();
    assert(check == "Tool");
    tool_text = s.GetString();
    tool_id = s.GetInt();
}

void Slider::serialize(ServerConnection s) {
    s.SendString("Slider");
    Tool::serialize(s);
    s.SendInt(available_positions);
    s.SendInt(current_state);
    //    s.SendInt(orientation);
}

void Slider::deserialize(ServerConnection s) {
    std::string check = s.GetString();
    assert(check == "Slider");
    Tool::deserialize(s);
    available_positions = s.GetInt();  // working?
    current_state = s.GetInt();
    //    orientation = static_cast<Orientation>(s.GetInt());
}
std::string Slider::tool_name() {
    return std::string("Slider");
}

void Button::serialize(ServerConnection s) {
    Tool::serialize(s);
}
void Button::deserialize(ServerConnection s) {
    std::string check = s.GetString();
    assert(check == "Button");
    Tool::deserialize(s);
    current_state = static_cast<ButtonState>(s.GetInt());  // working?
}

std::string Button::tool_name() {
    return std::string("Button");
}
