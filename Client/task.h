#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QGroupBox>
#include <string>
#include "ServerConnection.h"

class Task
{
public:
    QGroupBox *gr;
    std::string task_text = "Task text";
    int task_id  = 0;
    Task(QString s = "Task");
    virtual std::string GetName() {
        return "Task";
    }
    virtual void serialize(ServerConnection);
    virtual void deserialize(ServerConnection);
};

#endif // TASK_H
