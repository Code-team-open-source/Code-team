#include "sliders.h"

Sliders::Sliders()
{
    sl = new QSlider(Qt::Horizontal);
    l = new QLabel("1             2               3             4");
    sl->setStyleSheet("QSlider::groove:horizontal {"
                           "background: red;"
                           "position: absolute;"
                           "left: 4px; right: 4px;"
                       "}"

                       "QSlider::handle:horizontal {"
                           "width: 10px;"
                           "background:  darkblue;"
                           "margin: 0 -4px;"
                       "}"

                       "QSlider::add-page:horizontal {"
                           "background: white;"
                       "}"

                       "QSlider::sub-page:horizontal {"
                           "background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 cyan, stop:1 blue);"
                       "}");
    //sl->setStyleSheet("QSlider::groove:horizontal { background: blue; position: absolute;left: 1px; right: 1px;}"
    //                  "QSlider::handle:horizontal {width: 40px;background: green; margin: 0 -4px;}");
    l->setStyleSheet("color: black; font: bold 40px;");
    lv = new QVBoxLayout();
    lv->addWidget(l);
    lv->addWidget(sl);
    lv->addWidget(empty);
    sl->setMaximum(3);
}
