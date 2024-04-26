#include <SFML/Graphics.hpp>
#include <iostream>

#include "display.h"

using namespace sf;
using namespace std;

TicTacToeDisplay::TicTacToeDisplay() {
    // Load font
    if (!_font.loadFromFile("fonts/CaviarDreams.ttf")) {
        cerr << "font loading error" << endl;
    }
    _font.loadFromFile("fonts/CaviarDreams.ttf");

    // Shape vars
    const int BOARD_LENGTH = 650;
    const int BOARD_THICKNESS = 5;
    const int SQUARE_SIZE = 230;

    _boardVLine1.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
    _boardVLine1.setPosition(SQUARE_SIZE, 20);
    _boardVLine1.rotate(90);

    _boardVLine2.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
    _boardVLine2.setPosition(SQUARE_SIZE*2, 20);
    _boardVLine2.rotate(90);

    _boardHLine1.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
    _boardHLine1.setPosition(20, SQUARE_SIZE);

    _boardHLine2.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
    _boardHLine2.setPosition(20, SQUARE_SIZE*2);
}
void TicTacToeDisplay::displayBoard(RenderWindow& window) {
    window.draw(_boardVLine1);
    window.draw(_boardVLine2);
    window.draw(_boardHLine1);
    window.draw(_boardHLine2);
}

void TicTacToeDisplay::displayMenu(RenderWindow& window) {
    _menuText.setFont(_font);
    _menuText.setCharacterSize(80);
    _menuText.setString("Choose Player");
    _menuText.setFillColor(Color::White);
    _menuText.setPosition(80, 50);
    window.draw(_menuText);

    _xShape.setPosition(200, 380);
    _xShape.draw(window);
    _oShape.setPosition(490, 380);
    _oShape.draw(window);
}

char TicTacToeDisplay::checkChosenPlayer(const int X, const int Y) {
    if (_xShape.checkCollision(X, Y)) {
        return 'X';
    }
    else if (_oShape.checkCollision(X, Y)) {
        return 'O';
    }
    else {
        return '-';
    }

}