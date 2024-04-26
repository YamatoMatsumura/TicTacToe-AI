#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#include "xShape.h"
#include "oShape.h"

class TicTacToeDisplay {
    public:
        TicTacToeDisplay();
        void displayBoard(sf::RenderWindow& window);
        void displayMenu(sf::RenderWindow& window);

    private:
        XShape _xShape;
        OShape _oShape;
        sf::RectangleShape _xLine2;
        sf::RectangleShape _boardVLine1;
        sf::RectangleShape _boardVLine2;
        sf::RectangleShape _boardHLine1;
        sf::RectangleShape _boardHLine2;
        sf::Font _font;
        sf::Text _menuText;

};

#endif // DISPLAY_H