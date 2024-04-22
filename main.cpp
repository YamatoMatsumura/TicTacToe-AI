#include "board.h"
#include "ai.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
#include <iostream>
using namespace std;

int main() {

    // create a window
    RenderWindow window( VideoMode(690, 690), "Tic Tac Toe" );

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // create an event object once to store future events
    Event event;

    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        
        RectangleShape VLine1(Vector2f(590, 5));
        VLine1.setPosition(230, 50);
        VLine1.rotate(90);
        window.draw(VLine1);

        RectangleShape VLine2(Vector2f(590, 5));
        VLine2.setPosition(460, 50);
        VLine2.rotate(90);
        window.draw(VLine2);

        RectangleShape HLine1(Vector2f(590, 5));
        HLine1.setPosition(50, 230);
        window.draw(HLine1);

        RectangleShape HLine2(Vector2f(590, 5));
        HLine2.setPosition(50, 460);
        window.draw(HLine2);

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

        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////
    }



    return 0;
}