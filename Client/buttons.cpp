#include "buttons.h"

Buttons::Buttons() {
    b = new QPushButton("OFF");
    b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b->show();
    lh = new QVBoxLayout;
    lh->addWidget(b);
    b->setStyleSheet("QPushButton{background: red; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 red, stop:0.5 orange, stop:1 red); border:1px solid black;}");
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(but_clicked()));
}

void Buttons::but_clicked() {
    if (working) {
        working = false;
    } else {
        working = true;
    }
    if (working) {
        b->setStyleSheet("QPushButton{background: green; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 green, stop:0.5 lime, stop:1 green); border:1px solid black;}");
        if (b->text() == "OFF") {
            b->setText("ON");
        }
    } else {
        b->setStyleSheet("QPushButton{background: red; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 red, stop:0.5 orange, stop:1 red); border:1px solid black;}");
        if (b->text() == "ON") {
            b->setText("OFF");
        }
    }
}
