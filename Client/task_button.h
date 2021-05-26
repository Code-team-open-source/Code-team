#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H
#include "task.h"
#include <QGroupBox>
#include "buttons.h"
#include "ClientConnection.h"

class Task_button: public Task
{
public:
    int task_id = 0;
    int current_state = 0;
    std::string GetName() override {
        return "Button";
    }
    Buttons* bt;
    void serialize(ClientConnection&) override;
    void deserialize(ClientConnection&) override;
    Task_button(QString s = "Task", int id = 0);
    ~Task_button() override;
};

#endif // TASK_BUTTON_H
