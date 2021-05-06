#ifndef GIT_TOOL_H
#define GIT_TOOL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class Git_tool : QWidget
{
    Q_OBJECT
public:
    Git_tool(QWidget *parent = nullptr);
    QVBoxLayout * vl;
    QPushButton * push;
    QLineEdit *line;
public slots:
    void but_clicked();
};

#endif // GIT_TOOL_H
