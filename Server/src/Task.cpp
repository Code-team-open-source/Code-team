#include "Task.h"

Task::Task(std::string text, const Button &tool)
    : task_text(std::move(text)), tool(std::make_shared<Button>(tool)){};

Task::Task(std::string text, const Slider &tool)
    : task_text(std::move(text)), tool(std::make_shared<Slider>(tool)){};

int &Task::get_owner() {
    return task_owner_id;
}

void Task::change_status() {
    is_active ^= 1;
}

std::string Task::get_text() const {
    return task_text;
}

bool Task::active() const {
    return is_active;
}

std::shared_ptr<Tool> Task::get_tool() const {
    return tool;
}