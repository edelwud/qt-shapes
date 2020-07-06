#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent)
{

}

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent)
{

}

bool GraphicsView::IsSubset() {
    QList<QGraphicsItem*> elements = items();

    for (auto element : elements) {
        if (element->isUnderMouse()) {
            return true;
        }
    }
    return false;
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (IsSubset()) {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    for (std::function<void(QMouseEvent*)> callback : mousePressHandlers) {
        callback(event);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    for (std::function<void(QMouseEvent*)> callback : mouseReleaseHandlers) {
        callback(event);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (IsSubset()) {
        mouseReleaseEvent(event);
        return;
    }
    for (std::function<void(QMouseEvent*)> callback : mouseMoveHandlers) {
        callback(event);
    }
    QGraphicsView::mouseMoveEvent(event);
}

int GraphicsView::AddMousePressHandler(std::function<void(QMouseEvent*)> callback) {
    mousePressHandlers.append(callback);
    return mousePressHandlers.size() - 1;
}

int GraphicsView::AddMouseReleaseHandler(std::function<void(QMouseEvent*)> callback) {
    mouseReleaseHandlers.append(callback);
    return mouseReleaseHandlers.size() - 1;
}

int GraphicsView::AddMouseMoveHandler(std::function<void(QMouseEvent*)> callback) {
    mouseMoveHandlers.append(callback);
    return mouseMoveHandlers.size() - 1;
}

void GraphicsView::RemoveMouseMoveHandler(int identifier) {
    if (mouseMoveHandlers.size() <= identifier) {
        return;
    }
    mouseMoveHandlers.remove(identifier);
}

void GraphicsView::RemoveMousePressHandler(int identifier) {
    if (mousePressHandlers.size() <= identifier) {
        return;
    }
    mousePressHandlers.remove(identifier);
}

void GraphicsView::RemoveMouseReleaseHandler(int identifier) {
    if (mouseReleaseHandlers.size() <= identifier) {
        return;
    }
    mouseReleaseHandlers.remove(identifier);
}

