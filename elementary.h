#ifndef ELEMENTARY_H
#define ELEMENTARY_H

#include <QGraphicsItem>

enum class ElementaryFigures {
    Circle = 0,
    Rectangle,
    Triangle,
    Line
};

class Elementary : public QObject, public QGraphicsItem
{
public:
    Elementary();

    virtual ElementaryFigures getElement() = 0;
    void setPressHandler(std::function<bool(QGraphicsSceneMouseEvent*, bool)> handler);
    void setChosen(bool chosen);
    bool isChosen() const;
    QRectF boundingRect() const override = 0;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    bool chosen = false;
private:
    std::function<bool(QGraphicsSceneMouseEvent*, bool)> handler = [](QGraphicsSceneMouseEvent*, bool){ return false; };
};

#endif // ELEMENTARY_H
