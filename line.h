#ifndef LINE_H
#define LINE_H

#include <QPainter>
#include <elementary.h>
#include <figure.h>

class Line : public Elementary
{
public:
    Line(Figure* item1, Figure* item2);

    void setDotted(bool dotted);
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
