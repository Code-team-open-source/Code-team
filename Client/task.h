#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QGroupBox>

class Task
{
public:
    QGroupBox *gr;
    Task(QString s = "Task");
};

#endif // TASK_H
