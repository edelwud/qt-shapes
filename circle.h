#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPainter>
#include <figure.h>

class Circle : public Figure
{
public:
    Circle(qreal radius) : circleRadius(radius) {};
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    qreal circleRadius;
};

#endif // CIRCLE_H
