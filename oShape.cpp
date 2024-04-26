#include "oShape.h"

#include <SFML/Graphics.hpp>
using namespace sf;

OShape::OShape() {
    _circleOuter.setRadius(80);
    _circleOuter.setPointCount(200);
    _circleOuter.setOrigin(_circleOuter.getRadius(), _circleOuter.getRadius());

    _circleInner.setRadius(70);
    _circleInner.setPointCount(200);
    _circleInner.setOrigin(_circleInner.getRadius(), _circleInner.getRadius());
    _circleInner.setFillColor(Color::Black);
}

void OShape::setPosition(const double X, const double Y) {
    _circleOuter.setPosition(X, Y);
    _circleInner.setPosition(X, Y);
}

void OShape::draw(RenderWindow& window) {
    window.draw(_circleOuter);
    window.draw(_circleInner);
}