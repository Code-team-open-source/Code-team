#include "nlohmann/json.hpp"
#include "tasklib.h"
#include <iostream>
#include <string>

int InitialData::tool_count = 0;


int main() {
    tasklib tl("tasks.json");
    while(true) {
        std::cout << "Tool type: ";
        std::string tool_type;
        std::getline(std::cin, tool_type);
        if (tool_type == "exit") {
            break;
        }
        if (tool_type == "Button") {
            std::string tool_text;
            std::cout << "Tool text: ";
            std::getline(std::cin, tool_text);
            Button tool(tool_text);
            std::string task1_text;
            std::cout << "Button is not pushed finishes task: ";
            std::getline(std::cin, task1_text);
            Task task1(task1_text, Button(tool_text, ButtonState::NOT_PUSHED));
            std::string task2_text;
            std::cout << "Button is pushed finishes task: ";
            std::getline(std::cin, task2_text);
            Task task2(task2_text, Button(tool_text, ButtonState::PUSHED));
            std::vector<Task> tasks = {task1, task2};
            tl.add_tool(tool, tasks);
        } else if (tool_type == "Slider") {

        } else {
            std::cout << "Unknown tool type\n";
        }
    }
}

