#include "field.h"
#include "ui_field.h"

Field::Field(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Field)
{
    ui->setupUi(this);
    ind = new Main_indicators();
    ui->horizontalLayout_2->addWidget(ind->box);
    h1 = new QHBoxLayout;
    h2 = new QHBoxLayout;
    task.resize(10);
    for (int i = 0; i < 10 ; ++i ) {
        int k = rand() % 3;
        if (k == 1) {
            task[i] = new Task_button();
        }
        if (k == 2) {
            task[i] = new Task_buttons_6();
        }
        if (k == 0) {
            task[i] = new Task_sliders();
        }
    }

    for (int i = 0; i < 3 ; ++i ) {
        h1->addWidget(task[i]->gr);
        h2->addWidget(task[i + 3]->gr);
    }
    ui->v4->addLayout(h1);
    ui->v4->addLayout(h2);
}

Field::~Field()
{
    delete ui;
}

void Field::on_pushButton_clicked()
{
    fWindow = new Field();
    fWindow->show();
       this->close();
}
