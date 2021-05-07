#pragma once

#include <string>
#include "Task.h"

class tasklib {
    std::string source;

public:
    void add_tool(const Tool &, const std::vector<Task> &);
//    std::pair<const Tool &, const std::vector<Task> &> get_tool();

    tasklib(std::string file);
};