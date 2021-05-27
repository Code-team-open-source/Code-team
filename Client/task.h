#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QGroupBox>
#include <string>
#include "ClientConnection.h"

class Task
{
public:
    QGroupBox *gr;
    std::string task_text = "Task text";
    int task_id  = 0;
    Task(QString s = "Task", int id = 0);
    virtual ~Task();
    virtual std::string GetName() {
        return "Task";
    }

    virtual void serialize(ClientConnection&);
    virtual void deserialize(ClientConnection&);
    virtual void set_volume(int x);
};

#endif // TASK_H
