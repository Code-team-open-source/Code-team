#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game_field.h"
#include "creator_of_tasks.h"
#include "settings.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_quit_clicked();

    void on_settings_clicked();

private:
    Ui::MainWindow *ui;
    settings *settting;
    Game_field *fWindow;
    Creator_of_tasks *creator = nullptr;
public:
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
};
#endif // MAINWINDOW_H
