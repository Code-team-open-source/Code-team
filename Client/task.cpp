#include "task.h"
#include "ClientConnection.h"

Task::Task(QString s, int id)
{
    task_id = id;
    gr = new QGroupBox(s);
    gr->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }"
                      "QGroupBox::title {subcontrol-position: top middle;} ");
}

void Task::serialize(ClientConnection s) {
    s.SendString("Tool");
    s.SendString(task_text);
    s.SendInt(task_id);
}

void Task::deserialize(ClientConnection s) {
    std::string check = s.GetString();
    assert(check == "Tool");
    task_text = s.GetString();
    task_id = s.GetInt();
}
