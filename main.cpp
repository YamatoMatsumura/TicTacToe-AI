// Author: Yamato Matsumura
// Assignment: Final Project


#include "board.h"
#include "minimax.h"
#include "display.h"
#include "storage.h"


#include <iostream> 
using namespace std;
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

    //Game saving and loading files
    int nextSaveFileNum = getSaveFileCount() + 1; // +1 since next save file
    bool sPressed = false;
    bool inSaveFileMenu = false;
    bool lPressed = false;
    bool numKeyPressed = false;
    int keyPressedNum;

    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();
 
        if (inSaveFileMenu) {
            // Load tic tac toe board
            display.displayBoard(window);
            display.displayBoardMoves(window, board);
            // Load game over incase going into menu from game over
            if (board.gameOver()) {
                display.displayGameOver(window, board);
            }

            // check if any events happened since the last time checked
            while( window.pollEvent(event) ) {
                // if event type corresponds to pressing window X
                if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q)) {
                    // tell the window to close
                    window.close();
                }
                // Check for L press to exit menu
                if (Keyboard::isKeyPressed(Keyboard::L) && !lPressed) {
                    lPressed = true;
                    cout << "Exiting save file menu" << endl;
                    inSaveFileMenu = false;
                }
                // Check for L release
                if (!Keyboard::isKeyPressed(Keyboard::L)) {
                    lPressed = false;
                }

                // Check for which save file to load
                for (int i=1; i <= 9; i++) {
                    if ((Keyboard::isKeyPressed(Keyboard::Key(Keyboard::Num0 + i)) || 
                        Keyboard::isKeyPressed(Keyboard::Key(Keyboard::Numpad0 + i))) && 
                        getSaveFileCount() >= i && !numKeyPressed) {
                        
                        numKeyPressed = true;
                        keyPressedNum = i;
                        inSaveFileMenu = false;
                        loadSaveFile(i, board, player);

                        // Match game state variables to this save file
                        if (board.currentPlayer() == player) {
                            playerMove = true;
                        }
                        else {
                            playerMove = false;
                        }

                        if (player == 'X') {
                            computer = 'O';
                        }
                        else {
                            computer = 'X';
                        }
                    }
                    if (!Keyboard::isKeyPressed(Keyboard::Key(Keyboard::Num0 + keyPressedNum)) && 
                        !Keyboard::isKeyPressed(Keyboard::Key(Keyboard::Numpad0 + keyPressedNum))) {
                            numKeyPressed = false;
                    }
                }
            }
        }
        else {
            if (player == '-') {
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

                    // Check for L press for save file
                    if (Keyboard::isKeyPressed(Keyboard::L) && !lPressed) {
                        lPressed = true;
                        inSaveFileMenu = true;
                        showSaveFiles(getSaveFileCount());
                    }
                    // Check for L release
                    if (!Keyboard::isKeyPressed(Keyboard::L)) {
                        lPressed = false;
                    }
                }
            }
            // If player picked X or O
            else {
                // Load tic tac toe board
                display.displayBoard(window);
                display.displayBoardMoves(window, board);

                if (board.gameOver()) {
                    // Load game over
                    display.displayGameOver(window, board);
                    // check if any events happened since the last time checked
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
                        }

                        // Check for L press
                        if (Keyboard::isKeyPressed(Keyboard::L) && !lPressed) {
                            lPressed = true;
                            showSaveFiles(getSaveFileCount());
                            inSaveFileMenu = true;
                        }
                        // Check for L release
                        if (!Keyboard::isKeyPressed(Keyboard::L)) {
                            lPressed = false;
                        }

                    }
                }
                else {
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
                        }
                        // Check for S press
                        if (Keyboard::isKeyPressed(Keyboard::S) && !sPressed) {
                            sPressed = true;
                            saveGame(nextSaveFileNum, board.getBoardState(), getSaveFileCount(), player);
                        }
                        // Check for S release
                        if (!Keyboard::isKeyPressed(Keyboard::S)) {
                            sPressed = false;
                        }
                        // Check for L press
                        if (Keyboard::isKeyPressed(Keyboard::L) && !lPressed) {
                            lPressed = true;
                            showSaveFiles(getSaveFileCount());
                            inSaveFileMenu = true;
                        }
                        // Check for L release
                        if (!Keyboard::isKeyPressed(Keyboard::L)) {
                            lPressed = false;
                        }
                    }
                }
            }
        }

        // Display contents of current window
        window.display();
    }
    return 0;
}