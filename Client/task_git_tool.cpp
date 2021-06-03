#include "task_git_tool.h"

Task_git_tool::Task_git_tool(QString s, int id) : Task(s, id)
{
    git = new Git_tool();
    git->task_id = id;
    gr->setLayout(git->vl);
}

void Task_git_tool::serialize(ClientConnection &s) {
    s.SendString("CMD");
    Task::serialize(s);
    s.SendString(git->line->text().toStdString());
    git->line->setText("$ ");
}

void Task_git_tool::deserialize(ClientConnection &s) {
    Task::deserialize(s);
    git_text = s.GetString();
    git->task_id = task_id;
}

Task_git_tool::~Task_git_tool() {
    delete git;
}

void Task_git_tool::set_volume(int x) {
    git->n_player->setVolume(x);
    return;
}
