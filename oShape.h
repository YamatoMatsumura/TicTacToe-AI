#ifndef O_SHAPE_H
#define O_SHAPE_H

#include <SFML/Graphics.hpp>

class OShape {
    public:
        OShape();
        void setPosition(const int X, const int Y);
        void draw(sf::RenderWindow& window);
        bool checkCollision(const int X, const int Y);
    private:
        sf::CircleShape _circleOuter;
        sf::CircleShape _circleInner;
};

#endif // O_SHAPE_H