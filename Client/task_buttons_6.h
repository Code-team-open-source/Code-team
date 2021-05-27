#ifndef TASK_BUTTONS_6_H
#define TASK_BUTTONS_6_H
#include"task_button.h"
#include <QHBoxLayout>
#include <QString>

class Task_buttons_6 : public Task
{
public:
    QVBoxLayout *l;
    QHBoxLayout *ld;
    QHBoxLayout *lu;
    Buttons *bt11;
    Buttons *bt12;
    Buttons *bt13;
    Buttons *bt21;
    Buttons *bt22;
    Buttons *bt23;
    Task_buttons_6(QString s = "Task_6", int id = 0);
    ~Task_buttons_6() override;
    virtual void set_volume(int x) override;
};

#endif // TASK_BUTTONS_6_H
