#include "main_indicators.h"

Main_indicators::Main_indicators(QString s)
{
    timer = new QTimer;
    lh = new QVBoxLayout;
    bar = new QProgressBar;
    box = new QGroupBox(s);
    tx = new QTextBrowser;
    tx->setFont(QFont("Times", 20));
    box->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }");
    tx->setText("Проверить утечки памяти");
    lh->addWidget(bar);
    lh->addWidget(tx);
    box->setLayout(lh);
    bar->setStyleSheet("QProgressBar::chunk {background-color: purple ;width: 10px;margin: 0.5px;}");
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
