#include "task_sliders.h"

Task_sliders::Task_sliders(QString s) : Task(s)
{
    sl = new Sliders();
    sl->sl->show();
    gr->setLayout(sl->lv);
    gr->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }");
}
