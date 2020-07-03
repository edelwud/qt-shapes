#ifndef FIGURE_H
#define FIGURE_H

#include <elementary.h>

class Figure : public Elementary
{
public:
    Figure();
protected:
    QColor colour = Qt::black;
};

#endif // FIGURE_H
