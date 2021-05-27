#ifndef TASK_GIT_TOOL_H
#define TASK_GIT_TOOL_H
#include "task.h"
#include "git_tool.h"
#include "ClientConnection.h"

class Task_git_tool : public Task
{
public:
    std::string git_text;
    Git_tool *git;
    Task_git_tool(QString s = "Task", int id = 0);
    void serialize(ClientConnection&) override;
    void deserialize(ClientConnection&) override;
    ~Task_git_tool() override;
};

#endif // TASK_GIT_TOOL_H
