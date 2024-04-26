#ifndef X_SHAPE_H
#define X_SHAPE_H

#include <SFML/Graphics.hpp>

class XShape {
    public:
        XShape();
        void setPosition(const int X, const int Y);
        void draw(sf::RenderWindow& window);
        bool checkCollision(const int X, const int Y);

    private:
        sf::RectangleShape _xLine1;
        sf::RectangleShape _xLine2;      
};

#endif // X_SHAPE_H