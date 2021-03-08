#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buttons.h"
#include "QHBoxLayout"
#include "task_button.h"
#include "main_indicators.h"
#include "task_buttons_6.h"
#include "task_sliders.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: silver;");

    Main_indicators *mm = new Main_indicators();
    QHBoxLayout *l1 = new QHBoxLayout();
    QHBoxLayout *l2 = new QHBoxLayout();
    Task_button *f1 = new Task_button("Запустить valgrind");
    Task_sliders *sl1 = new Task_sliders("Установить мощность кулера");
    Task_sliders *sl2 = new Task_sliders("Поставить оценку ментору");
    Task_buttons_6 * b6 = new Task_buttons_6("Запустить сервер №");
    Task_buttons_6 * b66 = new Task_buttons_6("Запустить тест №");
    Task_button *f2 = new Task_button("Сделать коммит");
    mm->box->show();
    l1->addWidget(b6->gr);
    l2->addWidget(sl1->gr);
    l1->addWidget(f1->gr);
    l2->addWidget(f2->gr);
    l2->addWidget(b66->gr);
    l1->addWidget(sl2->gr);
    ui->v2->addWidget(mm->box);
    ui->v1->addLayout(l1);
    ui->v1->addLayout(l2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

