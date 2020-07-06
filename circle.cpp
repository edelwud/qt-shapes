#include "circle.h"

Circle::Circle(qreal radius) : circleRadius(radius) {}

ElementaryFigures Circle::getElement() {
    return ElementaryFigures::Circle;
}

QPointF Circle::getCore() {
    return QPointF(x() - circleRadius/2, y() - circleRadius/2);
}

QRectF Circle::boundingRect() const {
    return QRectF(-circleRadius, -circleRadius, circleRadius, circleRadius);
}

QRectF Circle::getArea() {
    return area;
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
    area.setCoords(0, 0, difference.x(), difference.y());
    update();
}
