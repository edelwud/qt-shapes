#include "figure.h"
#include <circle.h>
#include <triangle.h>

void Figure::setColour(QColor color) {
    colour = color;
}

Figure* Figure::createFigure(ElementaryFigures type) {
    Figure* p;
    switch (type)
    {
        default:
            assert(false);
    }
    return p;
}
