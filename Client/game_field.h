#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <QMainWindow>
#include <QDialog>
#include "task_button.h"
#include "task_dial.h"
#include "task_git_tool.h"
#include "task_buttons_6.h"
#include "task_sliders.h"
#include <QVector>
#include "main_indicators.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>


namespace Ui {
class Game_field;
}

class Game_field : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_field(QWidget *parent = nullptr);
    ~Game_field();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Main_indicators *ind;
    QVector<Task *> task;
    QHBoxLayout * h1;
    QHBoxLayout * h2;
    Ui::Game_field *ui;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
public:
    int i = 0;
    QTimer *timer;
    QMainWindow *m;
    //ClientConnection *client;
public slots:
    void for_timer();
};

#endif // GAME_FIELD_H
