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
    std::string get_text() const;
    int id() const ;
    virtual std::string tool_type() const = 0;
    virtual bool operator==(Tool *other) const = 0;
    virtual void serialize(ServerConnection);
    virtual void deserialize(ServerConnection);
    virtual std::string tool_name() = 0;
    virtual ~Tool() = default;
};

enum ButtonState {
    NOT_PUSHED,
    PUSHED,
};

class Button : public Tool {
private:
    ButtonState current_state = NOT_PUSHED;

public:
    Button(std::string text);
    Button(std::string text, ButtonState bs);
    ButtonState get_state() const;
    void change_state();
    bool operator==(Tool *other) const override;
    std::string tool_type() const override;
    void serialize(ServerConnection) override;
    void deserialize(ServerConnection) override;
    std::string tool_name() override;
};

class Slider : public Tool {
private:
    int available_positions = InitialData::slider_positions;
    int current_state = 1;

public:
    Slider(std::string text);
    Slider(std::string, int pos);
    int get_state() const;
    void set_state(int pos);
    void set_new_position(int new_position);
    std::string tool_type() const override;
    bool operator==(Tool *other) const override;
    void serialize(ServerConnection) override;
    void deserialize(ServerConnection) override;
    std::string tool_name() override;
};

