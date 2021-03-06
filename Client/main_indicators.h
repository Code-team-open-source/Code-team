#ifndef MAIN_INDICATORS_H
#define MAIN_INDICATORS_H
#include <QWidget>
#include <QProgressBar>
#include <QGroupBox>
#include <QString>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QTimer>

class Main_indicators: QWidget
{
public:
    Q_OBJECT

public:
    QTimer *timer;
    QTextBrowser *tx;
    QVBoxLayout *lh;
    QProgressBar *bar;
    QGroupBox *box;
    Main_indicators(QString s = "User Name");
public slots:
    void for_timer();
};

#endif // MAIN_INDICATORS_H
