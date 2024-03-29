#include "main_indicators.h"

Main_indicators::Main_indicators(QString s)
{
    timer = new QTimer;
    lh = new QVBoxLayout;
    bar = new QProgressBar;
    progress = new QProgressBar;
    progress->hide();
    box = new QGroupBox(s);
    tx = new QTextBrowser;
    tx->setFont(QFont("Times", 60));
    box->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }");
    tx->setText("");
    lh->addWidget(bar);
    lh->addWidget(progress);
    lh->addWidget(tx);
    box->setLayout(lh);
    bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 green, stop:1 lime); margin: 0.5px;}");
    progress->setStyleSheet("QProgressBar::chunk {background-color: blue ;margin: 0.5px;}");
    progress->setValue(50);
    bar->setFormat("");
    progress->setFormat("");
    bar->setValue(100);
    timer->setInterval(interval);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(for_timer()));

    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/hit1.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void Main_indicators::for_timer() {
    bar->setValue(bar->value() - 1);
    if (bar->value() < 67 and bar->value() > 34) {
        bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 darkYellow, stop:1 yellow); margin: 0.5px;}");
    }
    if (bar->value() < 34) {
        bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 darkRed, stop:1 red); margin: 0.5px;}");
    }
    if (bar->value() == 0) {
        n_player->play();
//        bar->setValue(100);
//        bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 green, stop:1 lime); margin: 0.5px;}");
//        timer->setInterval(100);
        run = 0;
    }
}

Main_indicators::~Main_indicators() {
    delete n_playlist;
    delete n_player;
    delete timer;
    delete tx;
    delete lh;
    delete bar;
    delete progress;
    delete box;
}
