#include "Tool.h"
#include <cassert>
#include <iostream>  // for tests
#include <utility>
#include "ServerConnection.h"

Tool::Tool(std::string text)
    : tool_text(std::move(text)), tool_id(InitialData::tool_count){};

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
    if (!(new_position > 0 && new_position <= available_positions)) {
        std::cerr << "error in slider set new position";
    }
    current_state = new_position;
}

std::string Slider::tool_type() const {
    return "Slider";
}

// new
// may be should be moved
// Oleg
// TODO
void Tool::serialize(SOCKET &s) {
    ServerConnection::SendString("Tool", s);
    ServerConnection::SendString(tool_text, s);
    ServerConnection::SendInt(tool_id, s);
}
void Tool::deserialize(SOCKET &s) {
    std::string check = ServerConnection::GetString(s);
    //    assert(check == "Tool");
    if (check != "Tool") {
        std::cerr << "i have desirealised not tool\n";
    }
    tool_text = ServerConnection::GetString(s);
    tool_id = ServerConnection::GetInt(s);
}

void Slider::serialize(SOCKET &s) {
    ServerConnection::SendString("Slider", s);
    Tool::serialize(s);
}

void Slider::deserialize(SOCKET &s) {
    Tool::deserialize(s);
    current_state = ServerConnection::GetInt(s);
}

void Button::serialize(SOCKET &s) {
    ServerConnection::SendString("Button", s);
    Tool::serialize(s);
}

void Button::deserialize(SOCKET &s) {
    Tool::deserialize(s);
    current_state = static_cast<ButtonState>(ServerConnection::GetInt(s));
}

CMD::CMD(std::string text, std::string cmd_text_)
    : Tool(std::move(text)), cmd_text(std::move(cmd_text_)) {
}

std::string CMD::get_cmd_text() const {
    return cmd_text;
}
void CMD::set_new_cmd_text(std::string new_text) {
    cmd_text = new_text;
}
std::string CMD::tool_type() const {
    return std::string("CMD");
}

void CMD::serialize(SOCKET &s) {
    ServerConnection::SendString("CMD", s);
    Tool::serialize(s);
    ServerConnection::SendString(cmd_text, s);
}

void CMD::deserialize(SOCKET &s) {
    Tool::deserialize(s);
    cmd_text = ServerConnection::GetString(s);
}
Dial::Dial(std::string text, int pos)
    : Tool(std::move(text)), current_state(pos) {
}
int Dial::get_state() const {
    return current_state;
}
void Dial::set_state(int pos) {
    current_state = pos;
}
std::string Dial::tool_type() const {
    return std::string("Dial");
}

void Dial::serialize(SOCKET &s) {
    ServerConnection::SendString("Dial", s);
    Tool::serialize(s);
    ServerConnection::SendInt(current_state, s);
}
void Dial::deserialize(SOCKET &s) {
    Tool::deserialize(s);
    current_state = ServerConnection::GetInt(s);
}
