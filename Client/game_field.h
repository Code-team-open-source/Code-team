#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <QMainWindow>
#include <QDialog>
#include "task_button.h"
#include "task_dial.h"
#include "task_git_tool.h"
#include "task_buttons_6.h"
#include "task_sliders.h"
#include "task_vertical_slider.h"
#include <QVector>
#include "main_indicators.h"

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
    Game_field *fWindow;
};

#endif // GAME_FIELD_H
