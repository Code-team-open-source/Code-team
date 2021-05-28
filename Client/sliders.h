#ifndef SLIDERS_H
#define SLIDERS_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "tool.h"

class Sliders : public QWidget
{
    Q_OBJECT
public:
    int task_id;
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    QSlider *sl;
    QLabel *l;
    QLabel *empty = new QLabel("");
    QVBoxLayout *lv;
    virtual ~Sliders();
    explicit Sliders(QWidget *parent = nullptr);
public slots:
    void but_clicked(int value);

signals:

};

#endif // SLIDERS_H
