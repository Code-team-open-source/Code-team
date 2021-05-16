#ifndef VERTICAL_SLIDER_H
#define VERTICAL_SLIDER_H
#include "sliders.h"
#include "tool.h"
#include <QHBoxLayout>

class vertical_slider : Tool
{
public:
    QSlider *sl;
    QLabel *l;
    QLabel *empty = new QLabel("");
    QHBoxLayout *lh;
    vertical_slider();
};

#endif // VERTICAL_SLIDER_H
