#include "Task.h"

namespace {
std::shared_ptr<Tool> make_shared(const Tool &tool) {
    if (tool.tool_type() == "Button") {
        return std::make_shared<Button>(dynamic_cast<const Button &>(tool));
    }
    if (tool.tool_type() == "Slider") {
        return std::make_shared<Slider>(dynamic_cast<const Slider &>(tool));
    }
    if (tool.tool_type() == "CMD") {
        return std::make_shared<CMD>(dynamic_cast<const CMD &>(tool));
    }

    return nullptr;
    // OTHER TOOLS
}
}  // namespace

Task::Task(std::string text, const Tool &tool_)
    : task_text(std::move(text)), tool(make_shared(tool_)){};

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