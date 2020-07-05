#include "elementary.h"

Elementary::Elementary()
{

}

void Elementary::setChosen(bool chosen) {
    this->chosen = chosen;
    update();
}

bool Elementary::isChosen() const {
    return chosen;
}

void Elementary::setPressHandler(std::function<bool (QGraphicsSceneMouseEvent *, bool)> handler) {
    this->handler = handler;
}

void Elementary::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    chosen = !chosen;
    handler(event, chosen);
    QGraphicsItem::mousePressEvent(event);
    update();
}
