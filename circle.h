#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPainter>
#include <cmath>
#include <figure.h>

class Circle : public Figure
{
public:
    Circle(qreal radius);

    QPointF getCore() override;
    void setSize(QPoint difference) override;
    QRectF boundingRect() const override;
private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    qreal circleRadius;
};

#endif // CIRCLE_H
