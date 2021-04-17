#include "task_button.h"
#include <QString>

Task_button::Task_button(QString s) : Task(s)
{
    bt = new Buttons();
    gr->setLayout(bt->lh);
}
