#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->settings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->pushButton_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    fWindow = new Game_field();
    fWindow->showFullScreen();
       this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(creator == nullptr) {
        creator = new Creator_of_tasks();
        creator->m = this;
    }
    creator->showFullScreen();
    this->hide();
}

void MainWindow::on_quit_clicked()
{
    this->close();
}
