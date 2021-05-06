#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H
#include "task.h"
#include <QGroupBox>
#include "buttons.h"
#include "ServerConnection.h"

class Task_button: public Task
{
public:
    int task_id = 0;
    int current_state = 0;
    std::string GetName() override {
        return "Button";
    }
    Buttons* bt;
    void serialize(ServerConnection) override;
    void deserialize(ServerConnection) override;
    Task_button(QString s = "Task");
};

#endif // TASK_BUTTON_H
