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
    ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label->setFont(QFont("Times", 20));
    ui->lineEdit->setFont(QFont("Times", 20));
    ui->box->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; border: 2px solid grey}");
    ui->pushButton->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    ui->pushButton_2->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    ui->settings->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    ui->quit->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    ui->ready->hide();
    ui->start->hide();
    ui->start->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    ui->ready->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");

    ui->ready->setEnabled(false);


    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/but1.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);



    m_player = new QMediaPlayer();
    m_playlist = new QMediaPlaylist(m_player);

    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sound/s2.wav"));
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    m_player->play();

    settting = new settings();
    settting->m = this;
    settting->m1_player = m_player;
    settting->n1_player = n_player;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == NULL) {
        ui->lineEdit->setStyleSheet("QLineEdit{border: 2px solid red;}");
        return;
    }
    if (fWindow != nullptr) {
        delete fWindow;
    }
    fWindow = new Game_field();
    fWindow->m = this;
    name = ui->lineEdit->text().toStdString();
    ui->pushButton->hide();
    ui->ready->show();
    ui->start->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    n_player->play();
    if(creator == nullptr) {
        creator = new Creator_of_tasks();
        creator->m = this;
    }
    creator->n_player->setVolume(sound);
    creator->showFullScreen();
    this->hide();
}

void MainWindow::on_quit_clicked()
{
    n_player->play();
    this->close();
}

void MainWindow::on_settings_clicked()
{
    n_player->play();
    settting->showFullScreen();
    this->hide();
}

void MainWindow::but_clicked() {
}

void MainWindow::on_start_clicked()
{
    n_player->play();
    m_player->stop();
    fWindow->showFullScreen();
       this->close();
}
