#include "oShape.h"

#include <SFML/Graphics.hpp>
using namespace sf;

OShape::OShape() {
    // Initialize outer circle
    _circleOuter.setRadius(80);
    _circleOuter.setPointCount(200);
    _circleOuter.setOrigin(_circleOuter.getRadius(), _circleOuter.getRadius());

    // Initialize inner circle to make O be hallow in center
    _circleInner.setRadius(70);
    _circleInner.setPointCount(200);
    _circleInner.setOrigin(_circleInner.getRadius(), _circleInner.getRadius());
    _circleInner.setFillColor(Color::Black);
}

void OShape::setPosition(const int X, const int Y) {
    _circleOuter.setPosition(X, Y);
    _circleInner.setPosition(X, Y);
}

void OShape::draw(RenderWindow& window) const {
    window.draw(_circleOuter);
    window.draw(_circleInner);
}

bool OShape::checkCollision(const int X, const int Y) const {
    const int floatX = static_cast<float> (X);
    const int floatY = static_cast<float> (Y);

    if (_circleOuter.getGlobalBounds().contains(Vector2f(floatX, floatY))) {
        return true;
    }
    else {
        return false;
    }
}