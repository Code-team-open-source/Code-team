#include "Tool.h"
#include <cassert>
#include <iostream>  // for tests
#include <utility>
#include "ServerConnection.h"

Tool::Tool(std::string text)
    : tool_text(std::move(text)), tool_id(InitialData::tool_count) {
    InitialData::tool_count++;
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
void Tool::serialize(ServerConnection& s) {
    s.SendString("Tool");
    s.SendString(tool_text);
    s.SendInt(tool_id);
}
void Tool::deserialize(ServerConnection& s) {
    std::string check = s.GetString();
    assert(check == "Tool");
    tool_text = s.GetString();
    tool_id = s.GetInt();
}

void Slider::serialize(ServerConnection& s) {
    s.SendString("Slider");
    Tool::serialize(s);
}

void Slider::deserialize(ServerConnection& s) {
    Tool::deserialize(s);
    current_state = s.GetInt();
}

void Button::serialize(ServerConnection& s) {
    s.SendString("Button");
    Tool::serialize(s);
}

void Button::deserialize(ServerConnection& s) {
    Tool::deserialize(s);
    current_state = static_cast<ButtonState>(s.GetInt());
}

CMD::CMD(std::string text, std::string cmd_text_) : Tool(std::move(text)), cmd_text(std::move(cmd_text_)) {}

std::string CMD::get_cmd_text() const {
    return cmd_text;
}
void CMD::set_new_cmd_text(std::string new_text) {
    cmd_text = new_text;
}
std::string CMD::tool_type() const {
    return std::string("CMD");
}
bool CMD::operator==(Tool *other) const {
    const auto *cmd = dynamic_cast<const CMD *>(other);
    assert(cmd);
    return  cmd_text == cmd->cmd_text;
}
void CMD::serialize(ServerConnection &s) {
    s.SendString("CMD");
    Tool::serialize(s);
    s.SendString(cmd_text);
}

void CMD::deserialize(ServerConnection &s) {
    Tool::deserialize(s);
    cmd_text = s.GetString();
}
Dial::Dial(std::string text, int pos) : Tool(std::move(text)), current_state(pos) {}
int Dial::get_state() const {
    return current_state;
}
void Dial::set_state(int pos) {
    current_state = pos;
}
std::string Dial::tool_type() const {
    return std::string("Dial");
}
bool Dial::operator==(Tool *other) const {
    const auto *dial = dynamic_cast<const Dial *>(other);
    assert(dial);
    return current_state == dial->get_state();
}

void Dial::serialize(ServerConnection &s) {
    s.SendString("Dial");
    Tool::serialize(s);
    s.SendInt(current_state);
}
void Dial::deserialize(ServerConnection &s) {
    Tool::deserialize(s);
    current_state = s.GetInt();
}
