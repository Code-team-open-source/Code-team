#include "task_vertical_slider.h"

task_vertical_slider::task_vertical_slider(QString s) : Task(s)
{
    slider = new vertical_slider();
    gr->setLayout(slider->lh);
}
