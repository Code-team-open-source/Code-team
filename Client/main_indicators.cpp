#include "main_indicators.h"

Main_indicators::Main_indicators(QString s)
{
    timer = new QTimer;
    lh = new QVBoxLayout;
    bar = new QProgressBar;
    box = new QGroupBox(s);
    tx = new QTextBrowser;
    tx->setText("Your current task");
    lh->addWidget(bar);
    lh->addWidget(tx);
    box->setLayout(lh);
    bar->setStyleSheet("QProgressBar::chunk {background-color: purple;}");
    bar->setValue(100);
    timer->setInterval(100);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(for_timer()));
}

void Main_indicators::for_timer() {
    bar->setValue(bar->value() - 1);
    if (bar->value() == 0) {
        bar->setValue(100);
        timer->setInterval(100);
    }
}
