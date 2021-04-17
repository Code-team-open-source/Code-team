#include "main_indicators.h"

Main_indicators::Main_indicators(QString s)
{
    timer = new QTimer;
    lh = new QVBoxLayout;
    bar = new QProgressBar;
    progress = new QProgressBar;
    box = new QGroupBox(s);
    tx = new QTextBrowser;
    tx->setFont(QFont("Times", 20));
    box->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; }");
    tx->setText("Проверить утечки памяти");
    lh->addWidget(bar);
    lh->addWidget(progress);
    lh->addWidget(tx);
    box->setLayout(lh);
    bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 green, stop:1 lime); margin: 0.5px;}");
    progress->setStyleSheet("QProgressBar::chunk {background-color: blue ;margin: 0.5px;}");
    progress->setValue(50);
    bar->setFormat("");
    progress->setFormat("");
    bar->setValue(100);
    timer->setInterval(100);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(for_timer()));
}

void Main_indicators::for_timer() {
    bar->setValue(bar->value() - 1);
    if (bar->value() < 67 and bar->value() > 34) {
        bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 darkYellow, stop:1 yellow); margin: 0.5px;}");
    }
    if (bar->value() < 34) {
        bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 darkRed, stop:1 red); margin: 0.5px;}");
    }
    if (bar->value() == 0) {
        bar->setValue(100);
        bar->setStyleSheet("QProgressBar::chunk {background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 green, stop:1 lime); margin: 0.5px;}");
        timer->setInterval(100);
    }
}
