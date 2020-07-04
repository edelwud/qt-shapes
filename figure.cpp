#include "figure.h"
#include <circle.h>

Figure* Figure::createFigure(ElementaryFigures type) {
    Figure* p;
    switch (type)
    {
        case ElementaryFigures::Triangle:
            p = new Triangle();
            break;
        case ElementaryFigures::Circle:
            p = new Circle(10, Qt::black);
            break;
        case ElementaryFigures::Square:
            p = new Square();
            break;
        default:
            assert(false);
    }
    return p;
}
