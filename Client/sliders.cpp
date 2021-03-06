#include "sliders.h"

Sliders::Sliders()
{
    sl = new QSlider(Qt::Horizontal);
    l = new QLabel("1                           2                          3                           4");
    lv = new QVBoxLayout();
    lv->addWidget(l);
    lv->addWidget(sl);
    lv->addWidget(empty);
    sl->setMaximum(3);
}
