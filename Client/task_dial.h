#ifndef TASK_DIAL_H
#define TASK_DIAL_H
#include <my_dial.h>
#include <task.h>

class Task_dial : public Task
{
public:
    My_dial *d;
    Task_dial(QString s = "Task");
};

#endif // TASK_DIAL_H
