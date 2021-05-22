#ifndef TASK_GIT_TOOL_H
#define TASK_GIT_TOOL_H
#include "task.h"
#include "git_tool.h"


class Task_git_tool : public Task
{
public:
    Git_tool *git;
    Task_git_tool(QString s = "Task");
    ~Task_git_tool() override;
};

#endif // TASK_GIT_TOOL_H
