#include "elementary.h"

Elementary::Elementary()
{

}

bool Elementary::isChosen() const {
    return chosen;
}

void Elementary::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    chosen = !chosen;
    QGraphicsItem::mousePressEvent(event);
    update();
}
