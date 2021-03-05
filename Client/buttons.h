#ifndef BUTTONS_H
#define BUTTONS_H
#include "tool.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class Buttons : public Tool
{
    Q_OBJECT
public:
    void show() const {
        b->show();
    }
    Buttons();
public:
    bool working = false;
    QPushButton *b;
    QVBoxLayout *lh;
public slots:
    void but_clicked();

};

#endif // BUTTONS_H
