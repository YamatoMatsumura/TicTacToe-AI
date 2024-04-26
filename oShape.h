#ifndef O_SHAPE_H
#define O_SHAPE_H

#include <SFML/Graphics.hpp>

class OShape {
    public:
        OShape();
        void setPosition(const double X, const double Y);
        void draw(sf::RenderWindow& window);
    private:
        sf::CircleShape _circleOuter;
        sf::CircleShape _circleInner;
};

#endif // O_SHAPE_H