// Author: Yamato Matsumura
// Assignment: Final Project

#ifndef X_SHAPE_H
#define X_SHAPE_H

#include <SFML/Graphics.hpp>

class XShape {
    public:
        /**
         * @brief Construct a new XShape object
         * 
         */
        XShape();
    
        /**
         * @brief Set the Position object
         * 
         * @param X - X coordinate
         * @param Y - Y coordinate
         */
        void setPosition(const int X, const int Y);

        /**
         * @brief Draws X shape to window
         * 
         * @param window - Window to draw to
         */
        void draw(sf::RenderWindow& window) const;

        /**
         * @brief Checks if given coordinate collides with X shape
         * 
         * @param X - X coordinate
         * @param Y - Y coordinate
         * @return true 
         * @return false 
         */
        bool checkCollision(const int X, const int Y) const;

    private:
        sf::RectangleShape _xLine1;
        sf::RectangleShape _xLine2;      
};

#endif // X_SHAPE_H