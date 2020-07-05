#include "rectangle.h"

Rectangle::Rectangle(qreal a, qreal b) : a(a), b(b)
{

}

QPointF Rectangle::getCore() {
    return QPointF(x() + a/2, y() + b/2);
}

QRectF Rectangle::boundingRect() const {
    return QRectF(0, 0, a, b);
}

void Rectangle::setSize(QPoint difference) {
    a = difference.x() - 5;
    b = difference.y() - 5;
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    const QPointF points[4] = {
        QPointF(0, 0),
        QPointF(0, b),
        QPointF(a, b),
        QPointF(a, 0)
    };
    if (chosen) {
        painter->setPen(QPen(Qt::red, 5));
    }
    painter->setBrush(colour);
    painter->drawPolygon(points, 4);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
