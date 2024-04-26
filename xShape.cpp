#include "xShape.h"

#include <SFML/Graphics.hpp>
using namespace sf;

XShape::XShape() {
    const int X_LENGTH = 160;
    const int X_THICKNESS = 10;

    _xLine1.setSize(Vector2f(X_LENGTH, X_THICKNESS));
    _xLine1.setOrigin(X_LENGTH/2, X_THICKNESS/2);
    _xLine1.rotate(45);

    _xLine2.setSize(Vector2f(X_LENGTH, X_THICKNESS));
    _xLine2.setOrigin(X_LENGTH/2, X_THICKNESS/2);
    _xLine2.rotate(135);
}

void XShape::setPosition(const double X, const double Y) {
    _xLine1.setPosition(X, Y);
    _xLine2.setPosition(X, Y);
}

void XShape::draw(RenderWindow& window) {
    window.draw(_xLine1);
    window.draw(_xLine2);
}