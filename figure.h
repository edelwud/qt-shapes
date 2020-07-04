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
    void setColour(QColor color);
    virtual void setSize(QPoint difference) = 0;
    static Figure* createFigure(ElementaryFigures type);
protected:
    QColor colour = Qt::black;
};

#endif // FIGURE_H
