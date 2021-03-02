#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buttons.h"
#include "QHBoxLayout"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QWidget * wdg = new QWidget(this);
    Buttons *r1 = new Buttons();
    Buttons *r2 = new Buttons();
    Buttons *r3 = new Buttons();
    Buttons *r4 = new Buttons();
    QHBoxLayout *l1 = new QHBoxLayout();
    QHBoxLayout *l2 = new QHBoxLayout();
    l1->addLayout(r1->lh);
    l1->addLayout(r2->lh);
    l2->addLayout(r3->lh);
    l2->addLayout(r4->lh);
    ui->v1->addLayout(l1);
    ui->v1->addLayout(l2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

