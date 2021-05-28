#include "task_sliders.h"

Task_sliders::Task_sliders(QString s, int id) : Task(s, id)
{
    sl = new Sliders();
    sl->task_id = id;
    gr->setLayout(sl->lv);
}

void Task_sliders::serialize(ClientConnection& s) {
    s.SendString("Slider");
    Task::serialize(s);
    s.SendInt(sl->sl->value());
}

void Task_sliders::deserialize(ClientConnection& s) {
    Task::deserialize(s);
    sl->task_id = task_id;
}

Task_sliders::~Task_sliders() {
    delete sl;
}

void Task_sliders::set_volume(int x) {
    sl->n_player->setVolume(x);
    return;
}
