#include "tasklib.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

tasklib::tasklib(std::string file) : source(std::move(file)) {};

void tasklib::add_tool(const Tool &tool, const std::vector<Task> &tasks) {
    json j;
    j["tool_type"] = tool.tool_type();
    j["tool_text"] = tool.get_text();
    json j_task;
    for (const auto &task : tasks) {
        j_task["task_text"] = task.get_text();
        if (task.get_tool()->tool_type() == "Button") {
            j_task["tool_position"] = dynamic_cast<const Button *>(task.get_tool().get())->get_state();
        }
        if (task.get_tool()->tool_type() == "Slider") {
            j_task["tool_position"] = dynamic_cast<const Slider *>(task.get_tool().get())->get_state();
        }
        j["tasks"].push_back(j_task);

/*
 *      for other tools
 *
 */
    }

    std::ifstream fin(source);
    if (!fin) {
        assert(1);
    }
    json lib;
    fin >> lib;
    fin.close();

    lib.push_back(j);
    std::ofstream fout(source);
    if (!fout) {
        assert(1);
    }
    fout << lib;
}

void tasklib::showlib() const {
    std::cout << "Parsed tasks\n";
    std::ifstream fin(source);
    if (!fin) {
        assert(1);
    }
    json lib;
    fin >> lib;
    std::cout << lib.dump(4);
    fin.close();
}