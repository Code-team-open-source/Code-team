#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buttons.h"
#include "QHBoxLayout"
#include "task_button.h"
#include "main_indicators.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Main_indicators *mm = new Main_indicators();
    QHBoxLayout *l1 = new QHBoxLayout();
    QHBoxLayout *l2 = new QHBoxLayout();
    Task_button *f1 = new Task_button();
    Buttons *b1 = new Buttons();
    Buttons *b2 = new Buttons();
    Task_button *f2 = new Task_button("New task");
    mm->box->show();
    l1->addLayout(b1->lh);
    l2->addLayout(b2->lh);
    l1->addWidget(f1->gr);
    l2->addWidget(f2->gr);
    ui->v2->addWidget(mm->box);
    ui->v1->addLayout(l1);
    ui->v1->addLayout(l2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

