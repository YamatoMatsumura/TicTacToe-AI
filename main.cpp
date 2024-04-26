#include "board.h"
#include "minimax.h"
#include "display.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
#include <iostream>
using namespace std;

int main() {
    // vector<char> boardState = {'-', '-', 'X', '-', 'X', '-', 'X', '-', '-'};
    Board board;
    TicTacToeDisplay display;

    // create a window
    RenderWindow window( VideoMode(690, 690), "Tic Tac Toe" );

    // create an event object once to store future events
    Event event;

    // Game vars
    int index;
    bool playerMove = true;
    char player = '-';
    char computer = '-';
    Vector2i mousePos;
    bool leftClicked = false;
    int bestMove;
    bool firstTimeThrough = true;  // Makes sure board loads first, then ai thinks about move to avoid lag

    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();
 
        if (player != '-') {
            // Load tic tac toe board
            display.displayBoard(window);
            display.displayBoardMoves(window, board);

            // Make ai move
            if (!firstTimeThrough && !playerMove) {
                bestMove = minimax(board);
                board.addMove(bestMove, computer);
                playerMove = true;
            }
            firstTimeThrough = false;

            // check if any events happened since the last time checked
            while( window.pollEvent(event) ) {
                // if event type corresponds to pressing window X
                if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q)) {
                    // tell the window to close
                    window.close();
                }
                // Check for left clicks
                if (Mouse::isButtonPressed(Mouse::Left) && !leftClicked && playerMove) {
                    mousePos = Mouse::getPosition(window);
                    index = display.getClickedSquare(mousePos.x, mousePos.y);
                    if (board.addMove(index, player)) {
                        playerMove = false;
                    }
                }
                // Check for left click release
                if (!Mouse::isButtonPressed(Mouse::Left)) {
                    leftClicked = false;
                }
                // Check for R press
                if (Keyboard::isKeyPressed(Keyboard::R)) {                    
                    board.restart();

                    // Reset variables
                    player = '-';
                    firstTimeThrough = true;
                    leftClicked = false;
                    break;
                }
            }
        }
        else {
            // Load menu screen
            display.displayMenu(window);
            // check if any events happened since the last time checked
            while( window.pollEvent(event) ) {
                // if event type corresponds to pressing window X
                if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q)) {
                    // tell the window to close
                    window.close();
                }
                // Check for left clicks
                if (Mouse::isButtonPressed(Mouse::Left) && !leftClicked) {
                    mousePos = Mouse::getPosition(window);
                    player = display.checkChosenPlayer(mousePos.x, mousePos.y);
                    if (player == 'O') {
                        playerMove = false;
                        computer = 'X';
                    }
                    if (player == 'X') {
                        computer = 'O';
                    }
                }
                if (!Mouse::isButtonPressed(Mouse::Left)) {
                    leftClicked = false;
                }
            }
        }

        if (board.gameOver()) {
            display.displayGameOver(window, board);
        }

        window.display();
    }

    return 0;
}