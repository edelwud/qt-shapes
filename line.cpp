#include "line.h"

Line::Line(Figure* item1, Figure* item2) : figure1(item1), figure2(item2)
{

}

void Line::setDotted(bool dotted) {
    this->dotted = dotted;
}

void Line::setColour(QColor colour) {
    this->colour = colour;
}

QRectF Line::boundingRect() const {
    return QRectF(figure1->getCore(), figure2->getCore());
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (chosen) {
        painter->setPen(QPen(Qt::red, 2));
    } else {
        painter->setPen(QPen(colour, 1, dotted ? Qt::PenStyle::DashLine : Qt::PenStyle::SolidLine));
    }
    painter->drawLine(QLineF(figure1->getCore(), figure2->getCore()));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
