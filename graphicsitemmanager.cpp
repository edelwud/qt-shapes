#include "graphicsitemmanager.h"

GraphicsItemManager::GraphicsItemManager(QGraphicsItemGroup* figures, QGraphicsItemGroup* lines) : figuresGroup(figures), linesGroup(lines)
{

}

void GraphicsItemManager::Pack(QString filename) {
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    int figuresSize = figuresGroup->childItems().size();
    file.write(reinterpret_cast<char*>(&figuresSize), sizeof (int));
    for (auto item : figuresGroup->childItems()) {
        Figure* figure = dynamic_cast<Figure*>(item);

        int figureType = (int)figure->getElement();
        file.write(reinterpret_cast<char*>(&figureType), sizeof (int));

        QPointF position = figure->pos();
        double x = position.x();
        double y = position.y();
        file.write(reinterpret_cast<char*>(&x), sizeof (double));
        file.write(reinterpret_cast<char*>(&y), sizeof (double));

        QRectF area = figure->getArea();
        double width = area.width();
        double height = area.height();
        file.write(reinterpret_cast<char*>(&width), sizeof (double));
        file.write(reinterpret_cast<char*>(&height), sizeof (double));

        QColor colour = figure->getColour();
        double colorValue = colour.rgb();
        file.write(reinterpret_cast<char*>(&colorValue), sizeof (double));
    }

    int linesSize = linesGroup->childItems().size();
    file.write(reinterpret_cast<char*>(&linesSize), sizeof (int));
    for (auto item : linesGroup->childItems()) {
        Line* line = dynamic_cast<Line*>(item);

        QPair<Figure*, Figure*> items = line->getItems();
        QPointF corePosition1 = items.first->getCore();
        double x1 = corePosition1.x();
        double y1 = corePosition1.y();
        file.write(reinterpret_cast<char*>(&x1), sizeof (double));
        file.write(reinterpret_cast<char*>(&y1), sizeof (double));

        QPointF corePosition2 = items.second->getCore();
        double x2 = corePosition2.x();
        double y2 = corePosition2.y();
        file.write(reinterpret_cast<char*>(&x2), sizeof (double));
        file.write(reinterpret_cast<char*>(&y2), sizeof (double));

        QColor colour = line->getColour();
        double colorValue = colour.rgb();
        file.write(reinterpret_cast<char*>(&colorValue), sizeof (double));

        bool dotted = line->getDotted();
        file.write(reinterpret_cast<char*>(&dotted), sizeof (bool));
    }
    file.close();
}

void GraphicsItemManager::Unpack(QString filename) {
    for (auto item : figuresGroup->childItems()) {
        delete item;
    }

    for (auto item : linesGroup->childItems()) {
        delete item;
    }

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    int figuresSize;
    file.read(reinterpret_cast<char*>(&figuresSize), sizeof (int));

    for (int i = 0; i < figuresSize; i++) {
        int figureType;
        file.read(reinterpret_cast<char*>(&figureType), sizeof (int));

        double x, y;
        file.read(reinterpret_cast<char*>(&x), sizeof (double));
        file.read(reinterpret_cast<char*>(&y), sizeof (double));

        double width, height;
        file.read(reinterpret_cast<char*>(&width), sizeof (double));
        file.read(reinterpret_cast<char*>(&height), sizeof (double));

        double colorValue;
        file.read(reinterpret_cast<char*>(&colorValue), sizeof (double));

        QColor colour;
        colour.setRgb(colorValue);

        Figure* figure = Figure::createFigure((ElementaryFigures)figureType, colour);
        figure->setSize(QPoint(width, height));
        figure->setPos(QPointF(x, y));
        figuresGroup->addToGroup(figure);
    }

    int linesSize;
    file.read(reinterpret_cast<char*>(&linesSize), sizeof (int));

    for (int i = 0; i < linesSize; i++) {
        double x1, y1;
        file.read(reinterpret_cast<char*>(&x1), sizeof (double));
        file.read(reinterpret_cast<char*>(&y1), sizeof (double));

        double x2, y2;
        file.read(reinterpret_cast<char*>(&x2), sizeof (double));
        file.read(reinterpret_cast<char*>(&y2), sizeof (double));

        double colorValue;
        file.read(reinterpret_cast<char*>(&colorValue), sizeof (double));

        bool dotted = false;
        file.read(reinterpret_cast<char*>(&dotted), sizeof (bool));

        Figure* figure1;
        for (auto item : figuresGroup->childItems()) {
            figure1 = dynamic_cast<Figure*>(item);
            QPointF position = figure1->getCore();
            double x = position.x();
            double y = position.y();
            if (x == x1 && y == y1) {
                break;
            }
        }

        Figure* figure2;
        for (auto item : figuresGroup->childItems()) {
            figure2 = dynamic_cast<Figure*>(item);
            QPointF position = figure2->getCore();
            double x = position.x();
            double y = position.y();
            if (x == x2 && y == y2) {
                break;
            }
        }

        Line* line = new Line(figure1, figure2);
        line->setDotted(dotted);
        QColor colour;
        colour.setRgb(colorValue);
        line->setColour(colour);
        linesGroup->addToGroup(line);
    }

}


















