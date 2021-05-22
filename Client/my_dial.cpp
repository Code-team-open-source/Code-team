#include "my_dial.h"

My_dial::My_dial(QWidget *parent) : QWidget(parent)
{
    qd = new QDial();
    vl = new QHBoxLayout();
    vh1 = new QVBoxLayout();
    vl->addWidget(qd);
    num = new QLCDNumber();
    vh1->addWidget(num);
    vh1->addWidget(empty);
    vl->addLayout(vh1);
    qd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    num->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(qd, SIGNAL(valueChanged(int)), this, SLOT(num_change(int)));
    num->display(1);
    qd->setStyleSheet("QDial { background-color:QLinearGradient("
            "x1: 0.177, y1: 0.004, x2: 0.831, y2: 0.911,"
            "stop: 0 white,"
            "stop: 0.061 white,"
            "stop: 0.066 lightgray,"
            "stop: 0.5 #242424,"
            "stop: 0.505 #000000,"
            "stop: 0.827 #040404,"
            "stop: 0.966 #292929,"
            "stop: 0.983 #2e2e2e);}");
    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/coin1.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void My_dial::num_change(int value) {
    int v = num->value();
    num->display(value / 10 + 1);
    if (v != num->value()) {
        n_player->play();
    }
}

My_dial::~My_dial() {
    delete n_playlist;
    delete n_player;
    delete num;
    delete qd;
    delete vh1;
    delete vl;
}
