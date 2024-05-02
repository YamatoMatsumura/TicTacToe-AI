// Author: Yamato Matsumura
// Assignment: Final Project

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#include "xShape.h"
#include "oShape.h"
#include "board.h"

class TicTacToeDisplay {
    public:
        /**
         * @brief Construct a new Tic Tac Toe Display object
         * 
         */
        TicTacToeDisplay();

        /**
         * @brief Draws tic tac toe board to screen
         * 
         * @param window - Window to draw to
         */
        void displayBoard(sf::RenderWindow& window) const;

        /**
         * @brief Draws initial menu of user picking X or O
         * 
         * @param window - Window to draw to
         */
        void displayMenu(sf::RenderWindow& window);

        /**
         * @brief Checks which piece player chose
         * 
         * @param X - X mouse coordinate
         * @param Y - Y mouse coordinate
         * @return char
         */
        char checkChosenPlayer(const int X, const int Y) const;

        /**
         * @brief Get the Clicked Square object
         * 
         * @param X - X mouse coordinate
         * @param Y - Y mouse coordinate
         * @return int - Index of clicked square
         */
        int getClickedSquare(const int X, const int Y) const;

        /**
         * @brief Draw all made moves in current board state to screen
         * 
         * @param window - Window to draw to
         * @param BOARD - Current board
         */
        void displayBoardMoves(sf::RenderWindow& window, const Board BOARD);

        /**
         * @brief Draw line across board indicating someone won
         * 
         * @param window - Window to draw to
         * @param BOARD  - Current board
         */
        void displayGameOver(sf::RenderWindow& window, const Board BOARD);


    private:
        XShape _xShape;
        OShape _oShape;
        sf::RectangleShape _xLine2;
        sf::RectangleShape _boardVLine1;
        sf::RectangleShape _boardVLine2;
        sf::RectangleShape _boardHLine1;
        sf::RectangleShape _boardHLine2;
        sf::RectangleShape _gameOverLine;
        sf::Font _font;
        sf::Text _menuText;
};

#endif // DISPLAY_H