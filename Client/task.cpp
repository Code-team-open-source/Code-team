#include "task.h"
#include "ServerConnection.h"

Task::Task(QString s)
{
    gr = new QGroupBox(s);
    gr->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }"
                      "QGroupBox::title {subcontrol-position: top middle;} ");
}

void Task::serialize(ServerConnection s) {
    s.SendString("Tool");
    s.SendString(task_text);
    s.SendInt(task_id);
}

void Task::deserialize(ServerConnection s) {
    std::string check = s.GetString();
    assert(check == "Tool");
    task_text = s.GetString();
    task_id = s.GetInt();
}
