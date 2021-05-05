#include "task_dial.h"

Task_dial::Task_dial(QString s) : Task(s)
{
    d = new My_dial();
    gr->setLayout(d->vl);
}
