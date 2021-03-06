#ifndef SLIDERS_H
#define SLIDERS_H
#include "tool.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>

class Sliders : Tool
{
public:
    QSlider *sl;
    QLabel *l;
    QLabel *empty = new QLabel("");
    QVBoxLayout *lv;
    Sliders();
};

#endif // SLIDERS_H
