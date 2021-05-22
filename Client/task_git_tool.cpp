#include "task_git_tool.h"

Task_git_tool::Task_git_tool(QString s) : Task(s)
{
    git = new Git_tool();
    gr->setLayout(git->vl);
}

Task_git_tool::~Task_git_tool() {
    delete git;
}
