#ifndef ELEMENTARY_H
#define ELEMENTARY_H

#include <QGraphicsItem>
#include <QDebug>

class Elementary : public QObject, public QGraphicsItem
{
public:
    Elementary();

    void setPressHandler(std::function<bool(QGraphicsSceneMouseEvent*, bool)> handler);
    void setChosen(bool chosen);
    bool isChosen() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool chosen = false;
private:
    std::function<bool(QGraphicsSceneMouseEvent*, bool)> handler = [](QGraphicsSceneMouseEvent*, bool){ return false; };
};

#endif // ELEMENTARY_H
