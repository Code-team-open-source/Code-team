#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class settings;
}

class settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::settings *ui;
public:
    int music;
    int sound;
    QMainWindow *m;
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    QMediaPlayer *m1_player;
    QMediaPlayer *n1_player;
};

#endif // SETTINGS_H
