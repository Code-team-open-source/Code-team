#include "task_button.h"
#include <QString>

Task_button::Task_button(QString s, int id) : Task(s, id)
{
    bt = new Buttons();
    gr->setLayout(bt->lh);
}

void Task_button::serialize(ClientConnection s) {
    s.SendString("Button");
    Task::serialize(s);
    s.SendInt(static_cast<int>(bt->working));
}

void Task_button::deserialize(ClientConnection s) {
    Task::deserialize(s);
}

Task_button::~Task_button() {
    delete bt;
}
