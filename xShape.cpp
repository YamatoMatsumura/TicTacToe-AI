// Author: Yamato Matsumura
// Assignment: Final Project

#include "xShape.h"

#include <SFML/Graphics.hpp>
using namespace sf;

XShape::XShape() {
    const int X_LENGTH = 160;
    const int X_THICKNESS = 10;

    // Initialize each line in X
    _xLine1.setSize(Vector2f(X_LENGTH, X_THICKNESS));
    _xLine1.setOrigin(X_LENGTH/2, X_THICKNESS/2);
    _xLine1.rotate(45);

    _xLine2.setSize(Vector2f(X_LENGTH, X_THICKNESS));
    _xLine2.setOrigin(X_LENGTH/2, X_THICKNESS/2);
    _xLine2.rotate(135);
}

void XShape::setPosition(const int X, const int Y) {
    _xLine1.setPosition(X, Y);
    _xLine2.setPosition(X, Y);
}

void XShape::draw(RenderWindow& window) const {
    window.draw(_xLine1);
    window.draw(_xLine2);
}

bool XShape::checkCollision(const int X, const int Y) const {
    const int floatX = static_cast<float> (X);
    const int floatY = static_cast<float> (Y);

    if (_xLine1.getGlobalBounds().contains(Vector2f(floatX, floatY)) || _xLine2.getGlobalBounds().contains(Vector2f(floatX, floatY))) {
        return true;
    }
    else {
        return false;
    }
}
