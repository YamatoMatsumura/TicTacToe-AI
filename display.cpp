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

    _gameOverLine.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS * 1.5));
    _gameOverLine.setFillColor(Color::Yellow);
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

int TicTacToeDisplay::getClickedSquare(const int X, const int Y) {
    const int WINDOW_WIDTH = 690;
    const int SQUARE_WIDTH = 230;
    int col = 0;
    int row = 0;
    for (int i=SQUARE_WIDTH; i <= WINDOW_WIDTH; i+= SQUARE_WIDTH) {
        if (X > i) {
            col += 1;
        }

        if (Y > i) {
            row += 1;
        }
    }

    // Get index of board vector from row & column
    int index = row * 3 + col;
    return index;
}

void TicTacToeDisplay::displayBoardMoves(RenderWindow& window, const Board BOARD) {
    const int BOARD_SIZE = 9;
    const int PIECE_OFFSET = 115;
    int rowOffset = 1;
    int colOffset = 1;
    for (int i=0; i < BOARD_SIZE; i++) {
        if (BOARD.getBoardState().at(i) == 'X') {
            _xShape.setPosition(PIECE_OFFSET * rowOffset, PIECE_OFFSET * colOffset);
            _xShape.draw(window);
        }
        if (BOARD.getBoardState().at(i) == 'O') {
            _oShape.setPosition(PIECE_OFFSET * rowOffset, PIECE_OFFSET * colOffset);
            _oShape.draw(window);
        }

        if (rowOffset == 5) {
            rowOffset = 1;
            colOffset += 2;
        }
        else {
            rowOffset += 2;
        }
    }
}

void TicTacToeDisplay::displayGameOver(RenderWindow& window, const Board BOARD) {
    const int PIECE_OFFSET = 115;
    const int BOARD_LENGTH = 650;
    char winPlayer = BOARD.winner();
    int hCount = 0;
    int vCount = 0;
    int rowIter = 0;
    int colIter = 0;    

    for (size_t i=0; i < BOARD.getBoardState().size(); i++) {
        // Check horizontal
        if (BOARD.getBoardState().at(i) == winPlayer) {
            hCount += 1;
        }

        if (hCount == 3) {
            // (i+1)/3 - 1 gets 0, 1, or 2 depending on which row
            // multiply by 2 to account for 2 offsets in each square
            _gameOverLine.setPosition(15, PIECE_OFFSET + PIECE_OFFSET * ((i+1)/3 - 1) * 2);
            window.draw(_gameOverLine);
        }

        if ((i+1) % 3 == 0) {
            // Reset count is end of row is reached
            hCount = 0;
        }

        // Check vertical
        if (BOARD.getBoardState().at(rowIter + colIter) == winPlayer) {
            vCount += 1;
        }

        if (vCount == 3) {
            // (i+1)/3 - 1 gets 0, 1, or 2 depending on which row
            // multiply by 2 to account for 2 offsets in each square
            // + 3.25 to account for rotation offset
            _gameOverLine.setPosition((PIECE_OFFSET + PIECE_OFFSET * ((i+1)/3 - 1) * 2) + 3.25, 15);
            _gameOverLine.rotate(90);
            window.draw(_gameOverLine);
            // Undo rotation so doesn't mess up next one
            _gameOverLine.rotate(270);
        }

        if ((i+1) % 3 == 0) {
            // Adjust iterators and reset count if end of column
            colIter += 1;
            rowIter = 0;
            vCount = 0;
        }
        else {
            rowIter += 3;
        }

        // Check for diagnol
        if (BOARD.getBoardState().at(4) == winPlayer) {
            int checkPos[2][2] = {{0, 8}, {2, 6}};
            for (int i=0; i < 2; i++) {
                bool diagnolWin = true;
                for (int j=0; j < 2; j++) {
                    if (BOARD.getBoardState().at(checkPos[i][j]) != winPlayer) {
                        diagnolWin = false;
                    }
                }
                if (diagnolWin) {
                    // Adjust for needing longer line b/c diagnol
                    _gameOverLine.setSize(Vector2f(919.24, 5 * 1.5));

                    if (i == 0) {
                        _gameOverLine.setPosition(15 + 5, 15);
                        _gameOverLine.rotate(45);
                        window.draw(_gameOverLine);
                        // Undo rotation so doesn't mess up next one
                        _gameOverLine.rotate(315);
                    }
                    else {
                        _gameOverLine.setPosition(15, (BOARD_LENGTH + 15) + 3.5);
                        _gameOverLine.rotate(315);
                        window.draw(_gameOverLine);
                        // Undo rotation so doesn't mess up next one
                        _gameOverLine.rotate(45);
                    }
                }
            }
        }
    }
}