#pragma once

#include <string>
#include "Task.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class tasklib {
    std::string source;
    int task_number = 0;

public:
    void add_tool(const Tool &, const std::vector<Task> &);
    json get_tool();

    void showlib() const;

    tasklib(std::string file);
};