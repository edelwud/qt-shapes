#include "elementary.h"

Elementary::Elementary()
{

}

void Elementary::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit onElementClicked();
    QGraphicsItem::mousePressEvent(event);
}
