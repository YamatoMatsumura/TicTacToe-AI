#include "minimax.h"

using namespace std;


int minimax(Board board) {
    int bestMove;
    int bestValue;
    char currentPlayer = board.currentPlayer();

    if (currentPlayer == 'X') {
        max(board, bestMove, bestValue);
    }
    else if (currentPlayer == 'O') {
        min(board, bestMove, bestValue);
    }

    return bestMove;
}

void max(Board board, int& bestMove, int& bestValue) {
    int possibleMove;
    int possibleValue;

    if (board.gameOver()) {
        bestValue = board.evaulateBoard();
    }
    else {
        vector<int> valueList;
        vector<int> moveList = board.possibleMoves();
        // Loop through each possible move
        for (size_t i=0; i < moveList.size(); i++) {

            // Create new board and simulate making move
            Board newBoard = board;
            newBoard.addMove(moveList.at(i), 'X');
    
            // Call min with new board
            min(newBoard, possibleMove, possibleValue);

            possibleMove = moveList.at(i);        
            // Store all ending values in valueList    
            valueList.push_back(possibleValue);

            // If max value found, stop looking at more moves
            if (possibleValue == 1) {
                break;
            }
        }
        int maxValue = -1;
        int maxValueIndex = 0;
        // Find max value in valueList
        for (size_t i=0; i < valueList.size(); i++) {
            if (maxValue < valueList.at(i)) {
                maxValue = valueList.at(i);
                maxValueIndex = i;
            }
        }

        // Update best move and value
        bestMove = moveList.at(maxValueIndex);
        bestValue = maxValue;
    }
}


void min(Board board, int& bestMove, int& bestValue) {
    int possibleMove;
    int possibleValue;

    if (board.gameOver()) {
        bestValue = board.evaulateBoard();
    }
    else {
        vector<int> valueList;
        vector<int> moveList = board.possibleMoves();
        // Loop through each possible move
        for (size_t i=0; i < moveList.size(); i++) {

            // Create a new board and simulate making move
            Board newBoard = board;
            newBoard.addMove(moveList.at(i), 'O');

            // Call min with new board
            max(newBoard, possibleMove, possibleValue);

            possibleMove = moveList.at(i);
            // Store all ending values in valueList    
            valueList.push_back(possibleValue);

            // If min value found, stop looking at more moves
            if (possibleValue == -1) {
                break;
            }
        }
        int minValue = 1;
        int minValueIndex = 0;

        // Find min value in valueList
        for (size_t i=0; i < valueList.size(); i++) {
            if (minValue > valueList.at(i)) {
                minValue = valueList.at(i);
                minValueIndex = i;
            }
        }

        // Update best move and value
        bestMove = moveList.at(minValueIndex);
        bestValue = minValue;
    }
}
