#ifndef BUTTONS_H
#define BUTTONS_H
#include "tool.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Buttons : public Tool
{
    Q_OBJECT
public:
    Buttons();
    ~Buttons();
public:
    int task_id;
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    bool working = false;
    QPushButton *b;
    QVBoxLayout *lh;
public slots:
    void but_clicked();


};

#endif // BUTTONS_H
