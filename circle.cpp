#include "circle.h"

Circle::Circle(qreal radius, QColor colour) : Figure(colour), circleRadius(radius) {}

QRectF Circle::boundingRect() const {
    return QRectF(0, 0, circleRadius, circleRadius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (chosen) {
        painter->setPen(QPen(Qt::red, 5));
    }
    painter->setBrush(colour);
    painter->drawEllipse(QRectF(0, 0, circleRadius, circleRadius));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
