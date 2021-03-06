#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>

#include <QPainter>

#include <figure.h>

class Triangle : public Figure
{
public:
    Triangle(qreal side, qreal base);

    ElementaryFigures getElement() override;
    QRectF getArea() override;
    QPointF getCore() override;
    void setSize(QPoint difference) override;
    QRectF boundingRect() const override;
private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    qreal side;
    qreal base;
    qreal aside;
};

#endif // TRIANGLE_H
