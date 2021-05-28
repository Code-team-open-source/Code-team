#ifndef MAIN_INDICATORS_H
#define MAIN_INDICATORS_H
#include <QWidget>
#include <QProgressBar>
#include <QGroupBox>
#include <QString>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <ClientConnection.h>
#include <tool.h>

class Main_indicators: QWidget
{
public:
    Q_OBJECT

public:
    int interval = 100;
    int run = 1;
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    QTimer *timer;
    QTextBrowser *tx;
    QVBoxLayout *lh;
    QProgressBar *bar;
    QProgressBar *progress;
    QGroupBox *box;
    Main_indicators(QString s = "Игрок");
    ~Main_indicators();
public slots:
    void for_timer();
};

#endif // MAIN_INDICATORS_H
