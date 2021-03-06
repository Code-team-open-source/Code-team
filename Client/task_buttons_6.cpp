#include "task_buttons_6.h"

Task_buttons_6::Task_buttons_6(QString s)
{
    gr = new QGroupBox(s);
    bt11 = new Buttons();
    bt12 = new Buttons();
    bt13 = new Buttons();
    bt21 = new Buttons();
    bt22 = new Buttons();
    bt23 = new Buttons();
    bt11->b->setText("0");
    bt12->b->setText("1");
    bt13->b->setText("2");
    bt21->b->setText("3");
    bt22->b->setText("4");
    bt23->b->setText("5");
    l = new QVBoxLayout;
    lu = new QHBoxLayout;
    ld = new QHBoxLayout;
    lu->addLayout(bt11->lh);
    lu->addLayout(bt12->lh);
    lu->addLayout(bt13->lh);
    ld->addLayout(bt21->lh);
    ld->addLayout(bt22->lh);
    ld->addLayout(bt23->lh);
    l->addLayout(lu);
    l->addLayout(ld);
    gr->setLayout(l);
}
