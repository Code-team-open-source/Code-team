#ifndef CREATOR_OF_TASKS_H
#define CREATOR_OF_TASKS_H

#include <QMainWindow>

namespace Ui {
class Creator_of_tasks;
}

class Creator_of_tasks : public QMainWindow
{
    Q_OBJECT

public:
    explicit Creator_of_tasks(QWidget *parent = nullptr);
    ~Creator_of_tasks();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_create_clicked();

private:
    Ui::Creator_of_tasks *ui;
public:
    QMainWindow *m;
};

#endif // CREATOR_OF_TASKS_H
