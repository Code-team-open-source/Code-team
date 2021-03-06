#pragma once
#include "Player.h"

class Task {
    Player task_owner;
    std::string task_text;
    std::unique_ptr<Tool> tool;
    int time = InitialData::time_for_one_task; // in seconds

private:

};