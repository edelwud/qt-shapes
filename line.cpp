#include "line.h"

Line::Line(Figure* item1, Figure* item2) : figure1(item1), figure2(item2)
{

}

QPair<Figure*, Figure*> Line::getItems() {
    return QPair<Figure*, Figure*>(figure1, figure2);
}

ElementaryFigures Line::getElement() {
    return ElementaryFigures::Line;
}

bool Line::getDotted() const {
    return dotted;
}

void Line::setDotted(bool dotted) {
    this->dotted = dotted;
}

QColor Line::getColour() const {
    return colour;
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
