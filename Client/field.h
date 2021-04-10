#ifndef FIELD_H
#define FIELD_H

#include <QDialog>
#include "task_button.h"
#include "task_buttons_6.h"
#include "task_sliders.h"
#include <QVector>
#include "main_indicators.h"

namespace Ui {
class Field;
}

class Field : public QDialog
{
    Q_OBJECT

public:
    explicit Field(QWidget *parent = nullptr);
    ~Field();

private slots:
    void on_pushButton_clicked();

private:
    Main_indicators *ind;
    QVector<Task *> task;
    QHBoxLayout * h1;
    QHBoxLayout * h2;
    Ui::Field *ui;
    Field *fWindow;
};

#endif // FIELD_H
