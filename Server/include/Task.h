#pragma once
#include "Player.h"

class Task {
    int task_owner_id;
    bool is_active = false;
    std::string task_text;
    std::unique_ptr<Tool> tool;
    int time = InitialData::time_for_one_task; // in seconds

public:
    int &get_owner();
    bool active();
    void change_status();
};