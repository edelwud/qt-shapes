#ifndef FIGURE_H
#define FIGURE_H

#include <exception>

#include <elementary.h>

class Figure : public Elementary
{
public:
    virtual QPointF getCore() = 0;
    virtual QRectF getArea() = 0;
    QColor getColour() const;
    void setColour(QColor color);
    virtual void setSize(QPoint difference) = 0;
    static Figure* createFigure(ElementaryFigures type, QColor baseColour);
protected:
    QColor colour = Qt::black;
    QRectF area;
};

#endif // FIGURE_H
