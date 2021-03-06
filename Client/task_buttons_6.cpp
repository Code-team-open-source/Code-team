#include "task_buttons_6.h"

Task_buttons_6::Task_buttons_6(QString s, int id) : Task(s, id)
{
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
    bt11->task_id = id;
    bt12->task_id = id;
    bt13->task_id = id;
    bt21->task_id = id;
    bt22->task_id = id;
    bt23->task_id = id;
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

Task_buttons_6::~Task_buttons_6() {
    delete bt11;
    delete bt12;
    delete bt13;
    delete bt21;
    delete bt22;
    delete bt23;
    delete ld;
    delete lu;
    delete l;
}

void Task_buttons_6::set_volume(int x) {
    bt11->n_player->setVolume(x);
    bt12->n_player->setVolume(x);
    bt13->n_player->setVolume(x);
    bt21->n_player->setVolume(x);
    bt22->n_player->setVolume(x);
    bt23->n_player->setVolume(x);
    return;
}
