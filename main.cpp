#include "board.h"
#include "minimax.h"
#include "display.h"

#include <SFML/Graphics.hpp>
using namespace sf;



int main() {
    // create new board and display
    Board board;
    TicTacToeDisplay display;

    // create a window
    RenderWindow window( VideoMode(690, 690), "Tic Tac Toe" );

    // create an event object once to store future events
    Event event;

    // Game vars
    bool playerMove = true; // Tracks if player made a move or not
    bool leftClicked = false; // Makes sure left click was released
    bool boardLoaded = false;  // Makes sure board loads first, then ai thinks about move to avoid lag
    char player = '-';
    char computer = '-';
    Vector2i mousePos;

    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();
 
        // If player picked X or O
        if (player == 'X' || player == 'O') {
            // Load tic tac toe board
            display.displayBoard(window);
            display.displayBoardMoves(window, board);

            // Make ai move
            if (boardLoaded && !playerMove) {
                board.addMove(minimax(board), computer);
                playerMove = true;
            }

            // Update since board loaded
            boardLoaded = true;

            // check if any events happened since the last time checked
            while( window.pollEvent(event) ) {
                // if event type corresponds to pressing window X
                if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q)) {
                    // tell the window to close
                    window.close();
                }
                // Check for left clicks
                if (Mouse::isButtonPressed(Mouse::Left) && !leftClicked && playerMove) {
                    leftClicked = true;
                    mousePos = Mouse::getPosition(window);
                    if (board.addMove(display.getClickedSquare(mousePos.x, mousePos.y), player)) {
                        playerMove = false;
                    }
                    display.displayBoardMoves(window, board);
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
                    boardLoaded = false;
                    leftClicked = false;
                    break;
                }
            }
        }
        // If gameover
        else if (player == 'N') {
            // Load tic tac toe board
            display.displayBoard(window);
            display.displayBoardMoves(window, board);
            // Load game over
            display.displayGameOver(window, board);
            while( window.pollEvent(event) ) {
                // if event type corresponds to pressing window X
                if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q)) {
                    // tell the window to close
                    window.close();
                }
                // Check for R press
                if (Keyboard::isKeyPressed(Keyboard::R)) {                    
                    board.restart();

                    // Reset variables
                    player = '-';
                    boardLoaded = false;
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
                    leftClicked = true;
                    mousePos = Mouse::getPosition(window);
                    // Check which player user chose
                    player = display.checkChosenPlayer(mousePos.x, mousePos.y);
                    // if player chose O
                    if (player == 'O') {
                        // O goes second
                        playerMove = false;
                        computer = 'X';
                    }
                    // if player chose X
                    if (player == 'X') {
                        computer = 'O';
                    }
                }
                // Make sure left click is released
                if (!Mouse::isButtonPressed(Mouse::Left)) {
                    leftClicked = false;
                }
            }
        }

        if (board.gameOver()) {
            // Update player to signify game over
            player = 'N';
        }

        // Display contents of current window
        window.display();
    }
    return 0;
}