#ifndef ELEMENTARY_H
#define ELEMENTARY_H

#include <QGraphicsItem>
#include <QDebug>

class Elementary : public QObject, public QGraphicsItem
{
public:
    Elementary();
signals:
    void onElementClicked();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QColor colour;
};

#endif // ELEMENTARY_H
