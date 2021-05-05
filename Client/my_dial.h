#ifndef MY_DIAL_H
#define MY_DIAL_H
#include <QDial>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>

class My_dial : QWidget
{
    Q_OBJECT
public:
    QLabel *empty = new QLabel("");
    QLCDNumber *num;
    QDial *qd;
    QHBoxLayout *vl;
    QVBoxLayout *vh1;
    My_dial(QWidget *parent = nullptr);
public slots:
    void num_change(int value);
};

#endif // MY_DIAL_H
