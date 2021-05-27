#include "settings.h"
#include "ui_settings.h"

int sound = 0;
int music = 0;

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
    ui->box->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; border: 2px solid grey}");
    ui->pushButton->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");

    ui->label->setFont(QFont("Times", 20));
    ui->label_2->setFont(QFont("Times", 20));


    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/but1.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

settings::~settings()
{
    delete ui;
}

void settings::on_pushButton_clicked()
{
    n1_player->play();
    m->showFullScreen();
    this->hide();
}

void settings::on_horizontalSlider_valueChanged(int value)
{
    music = value;
    m1_player->setVolume(value);
}

void settings::on_horizontalSlider_2_valueChanged(int value)
{
    sound = value;
    n1_player->setVolume(value);
}
