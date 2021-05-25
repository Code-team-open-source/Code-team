#ifndef SLIDERS_H
#define SLIDERS_H
#include "tool.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Sliders : Tool
{
public:
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    QSlider *sl;
    QLabel *l;
    QLabel *empty = new QLabel("");
    QVBoxLayout *lv;
    Sliders();
    ~Sliders();
public slots:
    void num_change(int value);
};

#endif // SLIDERS_H
