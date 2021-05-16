#ifndef TASK_VERTICAL_SLIDER_H
#define TASK_VERTICAL_SLIDER_H
#include "task.h"
#include "vertical_slider.h"


class task_vertical_slider : public Task
{
public:
    vertical_slider * slider;
    task_vertical_slider(QString s = "Task");
};

#endif // TASK_VERTICAL_SLIDER_H
