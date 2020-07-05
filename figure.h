#ifndef FIGURE_H
#define FIGURE_H

#include <elementary.h>

enum class ElementaryFigures {
    Circle,
    Rectangle,
    Triangle
};

class Figure : public Elementary
{
public:
    virtual QPointF getCore() = 0;
    void setColour(QColor color);
    virtual void setSize(QPoint difference) = 0;
    static Figure* createFigure(ElementaryFigures type, QColor baseColour);
protected:
    QColor colour = Qt::black;
};

#endif // FIGURE_H
