#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QVector>
#include <functional>

class GraphicsView : public QGraphicsView
{
    bool IsSubset();

    QVector<std::function<void(QMouseEvent*)>> mousePressHandlers;
    QVector<std::function<void(QMouseEvent*)>> mouseReleaseHandlers;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    GraphicsView(QWidget* parent = nullptr);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

    int AddMousePressHandler(std::function<void(QMouseEvent*)> callback);
    void RemoveMousePressHandler(int index);
    int AddMouseReleaseHandler(std::function<void(QMouseEvent*)> callback);
    void RemoveMouseReleaseHandler(int index);
};

#endif // GRAPHICSSCENE_H
