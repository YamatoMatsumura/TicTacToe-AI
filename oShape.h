#ifndef O_SHAPE_H
#define O_SHAPE_H

#include <SFML/Graphics.hpp>

class OShape {
    public:
        /**
         * @brief Construct a new OShape object
         * 
         */
        OShape();
        /**
         * @brief Set the Position object
         * 
         * @param X - X coordinate
         * @param Y - Y Coordinate
         */
        void setPosition(const int X, const int Y);
        /**
         * @brief Draws O shape to given screen
         * 
         * @param window - Window to draw to
         */
        void draw(sf::RenderWindow& window) const;
        /**
         * @brief Checks if given coordinate collides with O Shape
         * 
         * @param X - X coordinate
         * @param Y - Y coordinate
         * @return true 
         * @return false 
         */
        bool checkCollision(const int X, const int Y) const;
    private:
        sf::CircleShape _circleOuter;
        sf::CircleShape _circleInner;
};

#endif // O_SHAPE_H