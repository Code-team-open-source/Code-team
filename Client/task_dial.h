#ifndef TASK_DIAL_H
#define TASK_DIAL_H
#include <my_dial.h>
#include <task.h>
#include "ClientConnection.h"

class Task_dial : public Task
{
public:
    My_dial *d;
    int current_state;
    Task_dial(QString s = "Task", int id = 0);
    void serialize(ClientConnection&) override;
    void deserialize(ClientConnection&) override;
    ~Task_dial() override;
    virtual void set_volume(int x) override;
};

#endif // TASK_DIAL_H
