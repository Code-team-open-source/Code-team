#include "task_sliders.h"

Task_sliders::Task_sliders(QString s, int id) : Task(s, id)
{
    sl = new Sliders();
    gr->setLayout(sl->lv);
}

void Task_sliders::serialize(ClientConnection& s) {
    s.SendString("Slider");
    Task::serialize(s);
    s.SendInt(sl->sl->value());
}

void Task_sliders::deserialize(ClientConnection& s) {
    Task::deserialize(s);
}

Task_sliders::~Task_sliders() {
    delete sl;
}
