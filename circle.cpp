#include "circle.h"


QRectF Circle::boundingRect() const {
    return QRectF(0, 0, circleRadius, circleRadius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(colour);
    painter->drawEllipse(QRectF(0, 0, circleRadius, circleRadius));

    QRectF r = boundingRect();
    r.setSize(r.size()-circleRadius*QSizeF(1, 1));
    r.translate(circleRadius*QPointF(1, 1));
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(r);
}
