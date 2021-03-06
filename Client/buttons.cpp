#include "buttons.h"

Buttons::Buttons() {
    b = new QPushButton("OFF");
    b->show();
    lh = new QVBoxLayout;
    lh->addWidget(b);
    b->setStyleSheet("background: red; border: 2px solid black;");
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(but_clicked()));
}

void Buttons::but_clicked() {
    if (working) {
        working = false;
    } else {
        working = true;
    }
    if (working) {
        b->setStyleSheet("background: green; border: 2px solid black;");
        if (b->text() == "OFF") {
            b->setText("ON");
        }
    } else {
        b->setStyleSheet("background: red; border: 2px solid black;");
        if (b->text() == "ON") {
            b->setText("OFF");
        }
    }
}
