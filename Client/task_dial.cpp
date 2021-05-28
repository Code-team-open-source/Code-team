#include "task_dial.h"

Task_dial::Task_dial(QString s, int id) : Task(s, id)
{
    d = new My_dial();
    d->task_id = id;
    gr->setLayout(d->vl);
}

Task_dial::~Task_dial() {
    delete d;
}

void Task_dial::serialize(ClientConnection &s) {
    s.SendString("Dial");
    Task::serialize(s);
    s.SendInt(d->qd->value());
}

void Task_dial::deserialize(ClientConnection &s) {
    Task::deserialize(s);
    current_state = s.GetInt();
    d->qd->setValue(current_state * 10 - 1);
    d->task_id = task_id;
}

void Task_dial::set_volume(int x) {
    d->n_player->setVolume(x);
    return;
}
