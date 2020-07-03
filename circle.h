#ifndef CIRCLE_H
#define CIRCLE_H

#include <figure.h>

class Circle : Figure
{
public:
    Circle();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // CIRCLE_H
