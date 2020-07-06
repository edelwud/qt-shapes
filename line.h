#ifndef LINE_H
#define LINE_H

#include <QPainter>

#include <elementary.h>
#include <figure.h>

class Line : public Elementary
{
public:
    Line(Figure* item1, Figure* item2);

    QPair<Figure*, Figure*> getItems();

    ElementaryFigures getElement() override;

    bool getDotted() const;
    void setDotted(bool dotted);

    QColor getColour() const;
    void setColour(QColor colour);

    QRectF boundingRect() const override;
private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    Figure* figure1;
    Figure* figure2;
    QColor colour = Qt::black;
    bool dotted = false;
};

#endif // LINE_H
