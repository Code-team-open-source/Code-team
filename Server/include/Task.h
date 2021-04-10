#pragma once
#include "Player.h"

class Task {
    int task_owner_id = -1;
    bool is_active = false;
    std::string task_text;
    const std::shared_ptr<Tool> tool;
    int time = InitialData::time_for_one_task; // in seconds

public:
    Task(std::string text, const Button &tool);
    Task(std::string text, const Slider &tool);

    int &get_owner();
    bool active();
    void change_status();
    std::shared_ptr<Tool> get_tool() const;


};