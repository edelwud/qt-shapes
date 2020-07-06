#ifndef GRAPHICSITEMMANAGER_H
#define GRAPHICSITEMMANAGER_H

#include <QString>
#include <QGraphicsItemGroup>
#include <QFile>

#include <figure.h>
#include <line.h>

class GraphicsItemManager
{
public:
    GraphicsItemManager(QGraphicsItemGroup* figures, QGraphicsItemGroup* lines);
    void Pack(QString filename);
    void Unpack(QString filename);
private:
    QGraphicsItemGroup* figuresGroup;
    QGraphicsItemGroup* linesGroup;
};

#endif // GRAPHICSITEMMANAGER_H
