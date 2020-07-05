#include "figure.h"
#include <circle.h>
#include <triangle.h>
#include <rectangle.h>

void Figure::setColour(QColor color) {
    colour = color;
}

Figure* Figure::createFigure(ElementaryFigures type) {
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
            assert(false);
    }
    return p;
}
