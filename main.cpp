#include "board.h"
#include "ai.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<char> boardState = {'X', 'O', '-', 'X', 'X', '-', '-', '-', 'O'};
    Board board(boardState);
    // int bestMove = minimax(board);
    // cout << bestMove << endl;

    // create a window
    RenderWindow window( VideoMode(690, 690), "Tic Tac Toe" );

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // create an event object once to store future events
    Event event;

    const int BOARD_LENGTH = 650;
    const int BOARD_THICKNESS = 5;
    const int SQUARE_SIZE = 230;
    const int X_LENGTH = 160;
    const int X_THICKNESS = 10;
    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        
        RectangleShape vLine1;
        vLine1.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
        vLine1.setPosition(SQUARE_SIZE, 20);
        vLine1.rotate(90);
        window.draw(vLine1);

        RectangleShape vLine2;
        vLine2.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
        vLine2.setPosition(SQUARE_SIZE*2, 20);
        vLine2.rotate(90);
        window.draw(vLine2);

        RectangleShape hLine1;
        hLine1.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
        hLine1.setPosition(20, SQUARE_SIZE);
        window.draw(hLine1);

        RectangleShape hLine2;
        hLine2.setSize(Vector2f(BOARD_LENGTH, BOARD_THICKNESS));
        hLine2.setPosition(20, SQUARE_SIZE*2);
        window.draw(hLine2);

        CircleShape circleOuter;
        circleOuter.setRadius(80);
        circleOuter.setPointCount(200);
        circleOuter.setPosition(35+SQUARE_SIZE, 35+SQUARE_SIZE);
        window.draw(circleOuter);

        CircleShape circleInner;
        circleInner.setRadius(70);
        circleInner.setPointCount(200);
        circleInner.setFillColor(Color::Black);
        circleInner.setPosition(45+SQUARE_SIZE, 45+SQUARE_SIZE);
        window.draw(circleInner);

        RectangleShape xLine1;
        xLine1.setSize(Vector2f(X_LENGTH, X_THICKNESS));
        xLine1.setOrigin(X_LENGTH/2, X_THICKNESS/2);
        xLine1.rotate(45);
        xLine1.setPosition(115, 115);
        window.draw(xLine1);

        RectangleShape xLine2;
        xLine2.setSize(Vector2f(X_LENGTH, X_THICKNESS));
        xLine2.setOrigin(X_LENGTH/2, X_THICKNESS/2);
        xLine2.rotate(135);
        xLine2.setPosition(115, 115);
        window.draw(xLine2);

        //  END  DRAWING HERE
        /////////////////////////////////////


        // display the current contents of the window
        window.display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        bool leftClicked = false;
        // check if any events happened since the last time checked
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q)) {
                // tell the window to close
                window.close();
            }
            // Check for left clicks
            if (Mouse::isButtonPressed(Mouse::Left) && !leftClicked) {
                Vector2i mousePos = Mouse::getPosition(window);
                leftClicked = true;
                board.getClickedSquare(mousePos.x, mousePos.y);
            }
            if (!Mouse::isButtonPressed(Mouse::Left)) {
                leftClicked = false;
            }
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////
    }



    return 0;
}