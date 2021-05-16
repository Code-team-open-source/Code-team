#include "vertical_slider.h"

vertical_slider::vertical_slider()
{
    lh = new QHBoxLayout();
    sl = new QSlider();
    l = new QLabel("1\n\n2\n\n3\n\n4");
    l->setStyleSheet("color: black; font: bold 30px;");
    sl->setStyleSheet("QSlider::groove:vertical {"
                           "background: red;"
                           "position: absolute;"
                           "left: 4px; right: 4px;"
                       "}"

                       "QSlider::handle:vertical {"
                           "height: 10px;"
                           "background:  darkblue;"
                           "margin: 0 -4px;"
                       "}"

                       "QSlider::add-page:vertical {"
                           "background: white;"
                       "}"

                       "QSlider::sub-page:vertical {"
                           "background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 cyan, stop:1 blue);"
                       "}");
    lh->addWidget(empty);
    lh->addWidget(sl);
    lh->addWidget(l);
    sl->setMaximum(3);
}
