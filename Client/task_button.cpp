#include "task_button.h"
#include <QString>

Task_button::Task_button(QString s)
{
    gr = new QGroupBox(s);
    gr->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }");
    bt = new Buttons();
    gr->setLayout(bt->lh);
}
