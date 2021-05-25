#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->horizontalSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->horizontalSlider_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //ui->label_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/but1.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    music = 100;
    sound = 100;
}

settings::~settings()
{
    delete ui;
}

void settings::on_pushButton_clicked()
{
    n_player->play();
    m->showFullScreen();
    this->hide();
}

void settings::on_horizontalSlider_valueChanged(int value)
{
    music = value;
    emit m1_player->setVolume(value);
//    assert(m1_player->volume() == value);
}

void settings::on_horizontalSlider_2_valueChanged(int value)
{
    sound = value;
    emit n1_player->setVolume(value);
}
