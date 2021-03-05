#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H
#include "task.h"
#include <QGroupBox>
#include "buttons.h"

class Task_button: public Task
{
public:
    QGroupBox *gr;
    Buttons *bt;
    Task_button(QString s = "Task");
};

#endif // TASK_BUTTON_H
