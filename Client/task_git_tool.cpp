#include "task_git_tool.h"

Task_git_tool::Task_git_tool(QString s, int id) : Task(s, id)
{
    git = new Git_tool();
    gr->setLayout(git->vl);
}

void Task_git_tool::serialize(ClientConnection &s) {
    s.SendString("CMD");
    Task::serialize(s);
    s.SendString(git->line->text().toStdString());
}

void Task_git_tool::deserialize(ClientConnection &s) {
    Task::deserialize(s);
    git_text = s.GetString();
    git->line->setText(QString::fromStdString(git_text));
}

Task_git_tool::~Task_git_tool() {
    delete git;
}
