#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
