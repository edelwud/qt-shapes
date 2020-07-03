#include "elementary.h"

Elementary::Elementary()
{

}

void Elementary::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    chosen = !chosen;
    QGraphicsItem::mousePressEvent(event);
}
