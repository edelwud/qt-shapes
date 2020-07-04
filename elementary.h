#ifndef ELEMENTARY_H
#define ELEMENTARY_H

#include <QGraphicsItem>
#include <QDebug>

class Elementary : public QObject, public QGraphicsItem
{
public:
    Elementary();
    bool isChosen() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool chosen = false;
};

#endif // ELEMENTARY_H
