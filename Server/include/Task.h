#pragma once
#include "Player.h"

class Task {
    std::string task_text;
    std::vector<Tool> tools;
    // vector we need in case we need to change several tools to do this task
    int time = InitialData::time_for_one_task; // in seconds
};