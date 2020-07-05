#include "line.h"

Line::Line(Figure* item1, Figure* item2) : figure1(item1), figure2(item2)
{

}

QRectF Line::boundingRect() const {
    return QRectF(figure1->getCore(), figure2->getCore());
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(colour);
    painter->drawLine(QLineF(figure1->getCore(), figure2->getCore()));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
