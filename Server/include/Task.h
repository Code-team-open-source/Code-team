#pragma once
#include "Player.h"

class Task {
    int task_owner_id = -1;
    bool is_active = false;
    std::string task_text;
    const std::shared_ptr<Tool> tool;
    int time = InitialData::time_for_one_task;  // in seconds

public:
    Task(std::string text, const Tool &tool);

    int &get_owner();
    bool active() const;
    std::string get_text() const;
    void change_status();
    std::shared_ptr<Tool> get_tool() const;
};