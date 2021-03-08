#include "buttons.h"

Buttons::Buttons() {
    b = new QPushButton("OFF");
    b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    b->show();
    lh = new QVBoxLayout;
    lh->addWidget(b);
    b->setStyleSheet("background: red; border: 2px solid black; font: bold 40px;");
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(but_clicked()));
}

void Buttons::but_clicked() {
    if (working) {
        working = false;
    } else {
        working = true;
    }
    if (working) {
        b->setStyleSheet("background: green; border: 2px solid black; font: bold 40px;");
        if (b->text() == "OFF") {
            b->setText("ON");
        }
    } else {
        b->setStyleSheet("background: red; border: 2px solid black; font: bold 40px;rR");
        if (b->text() == "ON") {
            b->setText("OFF");
        }
    }
}
