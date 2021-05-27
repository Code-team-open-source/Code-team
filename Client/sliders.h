#ifndef SLIDERS_H
#define SLIDERS_H
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "tool.h"

class Sliders : Tool
{
public:
    int task_id;
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    QSlider *sl;
    QLabel *l;
    QLabel *empty = new QLabel("");
    QVBoxLayout *lv;
    Sliders();
    virtual ~Sliders();
};

#endif // SLIDERS_H
