#pragma once
#include "Player.h"
#include <vector>

class Task {
    std::string task_text;
    std::vector<Tool> tools;
    // vector we need in case we need to change several tools to do this task

};