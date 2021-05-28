#include "task.h"
#include "ClientConnection.h"

Task::Task(QString s, int id) : task_text(s.toStdString())
{
    task_id = id;
    gr = new QGroupBox(s);
    gr->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }"
                      "QGroupBox::title {subcontrol-position: top middle;} ");
}

void Task::serialize(ClientConnection& s) {
    s.SendString("Tool");
    s.SendString(task_text);
    s.SendInt(task_id);
}

void Task::deserialize(ClientConnection& s) {
    std::string check = s.GetString();
//    assert(check == "Tool");
    if (check != "Tool")
        std::cerr << "Tool is not tool, task deserialise error\n";
    task_text = s.GetString();
    task_id = s.GetInt();
    printf("task id is = %d", task_id);
    gr->setTitle(QString::fromStdString(task_text));
}

Task::~Task() {
    delete gr;
}

void Task::set_volume(int x) {
    return;
}
