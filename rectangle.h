#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QPainter>

#include <figure.h>

class Rectangle : public Figure
{
public:
    Rectangle(qreal a, qreal b);

    ElementaryFigures getElement() override;
    QRectF getArea() override;
    QPointF getCore() override;
    void setSize(QPoint difference) override;
    QRectF boundingRect() const override;
private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    qreal a;
    qreal b;
};

#endif // RECTANGLE_H
