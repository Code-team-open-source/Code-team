#include "task_dial.h"

Task_dial::Task_dial(QString s) : Task(s)
{
    d = new My_dial();
    gr->setLayout(d->vl);
}

Task_dial::~Task_dial() {
    delete d;
}

void Task_dial::serialize(ClientConnection &s) {
    s.SendString("Dial");
    Task::serialize(s);
    s.SendInt(current_state);
}

void Task_dial::deserialize(ClientConnection &s) {
    Task::deserialize(s);
    current_state = s.GetInt();
    d->qd->setValue(current_state * 10 - 1);
}

