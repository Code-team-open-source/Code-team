#include "task_button.h"
#include <QString>

Task_button::Task_button(QString s)
{
    gr = new QGroupBox(s);
    bt = new Buttons();
    gr->setLayout(bt->lh);
}
