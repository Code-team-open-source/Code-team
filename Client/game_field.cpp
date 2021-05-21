#include "game_field.h"
#include "ui_game_field.h"

Game_field::Game_field(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_field)
{
    ui->setupUi(this);
    ind = new Main_indicators();
    ui->verticalLayout_2->addWidget(ind->box);
    h1 = new QHBoxLayout;
    h2 = new QHBoxLayout;
    task.resize(10);
    for (int i = 0; i < 10 ; ++i ) {
        int k = rand() % 5;
        if (k == 0) {
            task[i] = new Task_sliders();
        }
        if (k == 1) {
            task[i] = new Task_button();
        }
        if (k == 2) {
            task[i] = new Task_buttons_6();
        }
        if (k == 3) {
            task[i] = new Task_dial();
        }
        if (k == 4) {
            task[i] = new Task_git_tool();
        }
    }

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
