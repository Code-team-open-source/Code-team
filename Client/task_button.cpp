#include "task_button.h"
#include <QString>

Task_button::Task_button(QString s, int id) : Task(s, id)
{
    bt = new Buttons();
    bt->task_id = id;
    gr->setLayout(bt->lh);
}

void Task_button::serialize(ClientConnection& s) {
    s.SendString("Button");
    Task::serialize(s);
    s.SendInt(static_cast<int>(bt->working));
}

void Task_button::deserialize(ClientConnection& s) {
    Task::deserialize(s);
    bt->task_id = task_id;
    printf("\ngot button with task id - %d\n", task_id);
}

Task_button::~Task_button() {
    delete bt;
}

void Task_button::set_volume(int x) {
    bt->n_player->setVolume(x);
    return;
}
