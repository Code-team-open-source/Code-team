#include <string>
#include "game_field.h"
#include "ui_game_field.h"
#include "protocols.h"
#include <thread>
#include <chrono>
#include <cassert>

Game_field::Game_field(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_field)
{

    protocol client;
    ui->setupUi(this);
    ind = new Main_indicators();
    ui->verticalLayout_2->addWidget(ind->box);
    h1 = new QHBoxLayout;
    h2 = new QHBoxLayout;
    task.resize(11);
    for (int i = 0; i < 10 ; ++i ) {
        printf("got hera %d\n", i);
      task[i] = client.GetTool(i);
    }
    printf("got here 1");
//     client.s.m->setText(QString::fromStdString(client.GetString()));
//    client.SendString("gepa");
    //assert(0);
//    client.SendInt(10);
//    client.GetInt();
//        h1->addWidget(task[0]->gr);
    for (int i = 0; i < 3 ; ++i ) {
        h1->addWidget(task[i]->gr);
        h2->addWidget(task[i + 3]->gr);
    }
    ui->v4->addLayout(h1);
    ui->v4->addLayout(h2);

    m_player = new QMediaPlayer();
    m_playlist = new QMediaPlaylist(m_player);

    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sound/s3.wav"));
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    m_player->play();
}

Game_field::~Game_field()
{
    delete ui;
}

void Game_field::on_pushButton_clicked()
{
    m_player->stop();
    fWindow = new Game_field();
    fWindow->showFullScreen();
    this->close();
}

void Game_field::on_pushButton_2_clicked()
{
    m_player->stop();
    this->close();
}
