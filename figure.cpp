#include "figure.h"
#include <circle.h>
#include <triangle.h>
#include <rectangle.h>
#include <exception>

void Figure::setColour(QColor color) {
    colour = color;
    update();
}

Figure* Figure::createFigure(ElementaryFigures type, QColor baseColour) {
    Figure* p;
    switch (type)
    {
        case ElementaryFigures::Circle: {
            p = new Circle(0);
        }
        break;
        case ElementaryFigures::Triangle: {
            p = new Triangle(0, 0);
        }
        break;
        case ElementaryFigures::Rectangle: {
            p = new Rectangle(0, 0);
        }
        break;
        default:
            throw new std::exception();
    }
    p->setColour(baseColour);
    return p;
}
