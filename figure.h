#ifndef FIGURE_H
#define FIGURE_H

#include <elementary.h>

enum class ElementaryFigures {
    Circle,
    Square,
    Triangle
};

class Figure : public Elementary
{
public:
    Figure(QColor colour) : colour(colour) {};
    static Figure* createFigure(ElementaryFigures type);
protected:
    QColor colour = Qt::black;
};

#endif // FIGURE_H
