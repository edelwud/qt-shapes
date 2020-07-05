#include "circle.h"

Circle::Circle(qreal radius) : circleRadius(radius) {}

QRectF Circle::boundingRect() const {
    return QRectF(-circleRadius, -circleRadius, circleRadius, circleRadius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (chosen) {
        painter->setPen(QPen(Qt::red, 5));
    }
    painter->setBrush(colour);
    painter->drawEllipse(QRectF(-circleRadius, -circleRadius, circleRadius, circleRadius));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Circle::setSize(QPoint difference) {
    circleRadius = std::sqrt(std::pow(difference.x(), 2) + std::pow(difference.y(), 2));
    update();
}
