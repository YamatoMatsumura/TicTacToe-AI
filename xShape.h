#ifndef X_SHAPE_H
#define X_SHAPE_H

#include <SFML/Graphics.hpp>

class XShape {
    public:
        XShape();
        void setPosition(const double X, const double Y);
        void draw(sf::RenderWindow& window);
    private:
        sf::RectangleShape _xLine1;
        sf::RectangleShape _xLine2;      
};

#endif // X_SHAPE_H