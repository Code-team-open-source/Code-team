#include "git_tool.h"

namespace  cl{
int color = 0;
}

Git_tool::Git_tool(QWidget * parent) : QWidget(parent)
{
    cl::color = (cl::color + 1) % 2;
    vl = new QVBoxLayout();
    push = new QPushButton("Push");
    line = new QLineEdit();
    if (cl::color == 1) {
        line->setStyleSheet("QLineEdit{ border: 2px solid black; font: bold 40px;  background: black; color: lime;}");
    } else {
        line->setStyleSheet("QLineEdit{ border: 2px solid black; font: bold 40px;  background: black; color: yellow}");
    }
    push->setStyleSheet("QPushButton{ background: grey; border: 2px solid black; font: bold 40px;}"
                        "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    vl->addWidget(line);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vl->addWidget(push);
    line->setText("$ ");
    QObject::connect(push, SIGNAL(clicked()), this, SLOT(but_clicked()));

    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/but2.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void Git_tool::but_clicked() {
    n_player->play();
    line->clear();
    line->setText("$ ");
}
