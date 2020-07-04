#include "triangle.h"

Triangle::Triangle(qreal side, qreal base) : side(side), base(base)
{
    aside = std::sqrt(std::pow(side, 2) - std::pow(base, 2) / 4);
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
}


void Triangle::setSize(QPoint difference) {
    base = difference.x();
    aside = difference.y();
    update();
}
