#ifndef GIT_TOOL_H
#define GIT_TOOL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Git_tool : QWidget
{
    Q_OBJECT
public:
    QMediaPlayer *n_player;
    QMediaPlaylist *n_playlist;
    Git_tool(QWidget *parent = nullptr);
    ~Git_tool();
    QVBoxLayout * vl;
    QPushButton * push;
    QLineEdit *line;
public slots:
    void but_clicked();
};

#endif // GIT_TOOL_H
