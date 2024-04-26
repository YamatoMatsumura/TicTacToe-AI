#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#include "xShape.h"
#include "oShape.h"
#include "board.h"

class TicTacToeDisplay {
    public:
        TicTacToeDisplay();
        void displayBoard(sf::RenderWindow& window);
        void displayMenu(sf::RenderWindow& window);
        char checkChosenPlayer(const int X, const int Y);
        int getClickedSquare(const int X, const int Y);
        void displayBoardMoves(sf::RenderWindow& window, const Board BOARD);

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