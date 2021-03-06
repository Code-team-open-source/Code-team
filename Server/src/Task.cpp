#include "Task.h"

int &Task::get_owner() {
    return task_owner_id;
}

void Task::change_status() {
    is_active ^= 1;
}

bool Task::active() {
    return is_active;
}