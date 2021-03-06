#include "triangle.h"

Triangle::Triangle(qreal side, qreal base) : side(side), base(base)
{
    aside = std::sqrt(std::pow(side, 2) - std::pow(base, 2) / 4);
}

ElementaryFigures Triangle::getElement() {
    return ElementaryFigures::Triangle;
}

QRectF Triangle::getArea() {
    return area;
}

QPointF Triangle::getCore() {
    const qreal r = std::pow(side, 2) / std::sqrt(std::pow(2 * side, 2) - std::pow(base, 2));
    return QPointF(x() + base/2, y() + r);
}

QRectF Triangle::boundingRect() const {
    return QRectF(0, 0, base, aside);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    const QPointF points[3] = {
        QPointF(0, aside),
        QPointF(base / 2, 0),
        QPointF(base, aside)
    };
    if (chosen) {
        painter->setPen(QPen(Qt::red, 5));
    }
    painter->setBrush(colour);
    painter->drawPolygon(points, 3);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void Triangle::setSize(QPoint difference) {
    base = difference.x() - 5;
    aside = difference.y();
    side = std::sqrt(std::pow(base, 2) + std::pow(aside, 2));
    area.setCoords(0, 0, difference.x(), difference.y());
}
