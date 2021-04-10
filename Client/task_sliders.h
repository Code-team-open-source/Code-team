#ifndef TASK_SLIDERS_H
#define TASK_SLIDERS_H
#include "task_button.h"
#include "sliders.h"

class Task_sliders : public Task
{
public:
    Sliders *sl;
    Task_sliders(QString s = "Task");
};

#endif // TASK_SLIDERS_H
