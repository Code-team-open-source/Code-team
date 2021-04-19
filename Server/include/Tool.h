#pragma once
#include "InitialData.h"
#include "ServerConnection.h"
#include <string>

class Tool {
private:
    std::string tool_text;
    int tool_id;
public:
    Tool(std::string text);
    std::string get_text();
    int id() const ;
    virtual bool operator==(Tool *other) const = 0;
    virtual void serialize(ServerConnection);
    virtual void deserialize(ServerConnection);
    virtual std::string tool_name() = 0;
    virtual ~Tool() = default;
};

enum ButtonState {
    PUSHED,
    NOT_PUSHED,
};

class Button : public Tool {
private:
    ButtonState current_state = NOT_PUSHED;

public:
    Button(std::string text);
    ButtonState get_state() const;
    void change_state();
    bool operator==(Tool *other) const override;
    void serialize(ServerConnection) override;
    void deserialize(ServerConnection) override;
    std::string tool_name() override;
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
    bool operator==(Tool *other) const override;
    void serialize(ServerConnection) override;
    void deserialize(ServerConnection) override;
    std::string tool_name() override;
};

