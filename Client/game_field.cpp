#include <string>
#include "game_field.h"
#include "ui_game_field.h"
#include <thread>
#include <chrono>
#include "settings.h"

Game_field::Game_field(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_field)
{

    client = new ClientConnection;
    client->SendString("ABOBA");
    ui->setupUi(this);
    ind = new Main_indicators();
    ui->verticalLayout_2->addWidget(ind->box);
    h1 = new QHBoxLayout;
    h2 = new QHBoxLayout;
    task.resize(11);
    for (int i = 0; i < 6 ; ++i ) {
        printf("got hera %d\n", i);
      task[i] = client->GetTool();
    }
//    std::string str = client->GetString();
//    printf("%s\n", str.c_str());

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
    m_player->setVolume(music);
    ind->n_player->setVolume(sound);
    for (int i = 0; i < 6; i++) {
        task[i]->set_volume(sound);
    }

    timer = new QTimer();
    timer->setInterval(1);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(for_timer()));

    dialog = new QGroupBox("");
    ll1 = new QHBoxLayout();
    ll2 = new QHBoxLayout();
    rr = new QVBoxLayout();
    done_task_count = new QLabel("Tasks done");
    count = new QLabel("18");
    new_level = new QPushButton("New level");
    exit = new QPushButton("to main menu");
    exit->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    new_level->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    new_level->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    done_task_count->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    count->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ll1->addWidget(new_level);
    ll1->addWidget(exit);
    ll2->addWidget(done_task_count);
    ll2->addWidget(count);
    rr->addLayout(ll2);
    rr->addLayout(ll1);
    dialog->setLayout(rr);
    dialog->hide();
    ui->verticalLayout_4->addWidget(dialog);
    dialog->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; border: 2px solid grey}");
    done_task_count->setFont(QFont("Times", 40));
    count->setFont(QFont("Times", 40));
}

Game_field::~Game_field()
{
    delete ui;
    for (int i = 0; i < 10 ; ++i) {
        delete task[i];
    }
    delete ind;
    delete h1;
    delete h2;
    delete m_playlist;
    delete m_player;
}

void Game_field::on_pushButton_clicked()
{
    for (int i = 0; i < 10 ; ++i) {
        delete task[i];
    }
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

    for (int i = 0; i < 6; i++) {
        task[i]->set_volume(sound);
    }

    for (int i = 0; i < 3 ; ++i ) {
        h1->addWidget(task[i]->gr);
        h2->addWidget(task[i + 3]->gr);
    }
    ui->v4->addLayout(h1);
    ui->v4->addLayout(h2);
}

void Game_field::on_pushButton_2_clicked()
{
    m_player->stop();
    this->hide();
    m->showFullScreen();
}


void Game_field::for_timer() {
    while (i != vec.size()) {
        client->SendString("Tool changed");
        client->SendInt(vec[i].first);
        client->SendString(vec[i].second);
        i++;
    }
    ind->progress->setValue(ind->progress->value() + 1);
    timer->setInterval(1);
}
