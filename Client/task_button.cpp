#include "task_button.h"
#include <QString>

Task_button::Task_button(QString s) : Task(s)
{
    bt = new Buttons();
    gr->setLayout(bt->lh);
}

void Task_button::serialize(ServerConnection s) {
    s.SendString("Button");
    Task::serialize(s);
    s.SendInt(current_state);
}

void Task_button::deserialize(ServerConnection s) {
    std::string check = s.GetString();
    assert(check == "Button");
    Task::deserialize(s);
    current_state = s.GetInt();
}
