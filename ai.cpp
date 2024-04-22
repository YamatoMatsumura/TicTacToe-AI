#include "ai.h"

#include <vector> // Might not need
#include <iostream> // delete after testing

using namespace std;


int evaluateBoard(const Board BOARD) {
    if (BOARD.winner() == 'X') {
        return 1;
    }
    else if (BOARD.winner() == 'O') {
        return -1;
    }
    else {
        return 0;
    }
}

int minimax(Board board) {
    char currentPlayer = board.currentPlayer();
    int bestMove = 999;
    int bestValue = 999;
    if (currentPlayer == 'X') {
        max(board, bestMove, bestValue);
    }
    else if (currentPlayer == 'O') {
        min(board, bestMove, bestValue);
    }
    return bestMove;
}

void max(Board board, int& bestMove, int& bestValue) {
    int possibleMove = 999;
    int possibleValue = 999;

    if (board.gameOver()) {
        bestValue = evaluateBoard(board);
        cout << "gameOver, max value: " << bestValue << endl;
    }
    else {
        vector<int> valueList;
        vector<int> moveList = board.possibleMoves();
        for (size_t i=0; i < moveList.size(); i++) {
            Board newBoard = board;
            newBoard.addMove(moveList.at(i), 'X');
            cout << "max: " << endl; 
            cout << newBoard << endl;
            min(newBoard, possibleMove, possibleValue);
            possibleMove = moveList.at(i);
            cout << "possibleMove (max): " << possibleMove << endl;
            cout << "possibleValue (max): " << possibleValue << endl;
            
            valueList.push_back(possibleValue);
            if (possibleValue == 1) {
                // cout << "exiting max early" << endl;
                break;
            }
        }
        int maxValue = -1;
        int maxValueIndex = 0;
        for (size_t i=0; i < valueList.size(); i++) {
            if (maxValue < valueList.at(i)) {
                maxValue = valueList.at(i);
                maxValueIndex = i;
            }
        }
        // cout << "max: " << maxValueIndex << endl;
        bestMove = moveList.at(maxValueIndex);
        bestValue = maxValue;
    }
    return;
}


void min(Board board, int& bestMove, int& bestValue) {
    int possibleMove = 999;
    int possibleValue = 999;

    if (board.gameOver()) {
        bestValue = evaluateBoard(board);
        cout << "gameOver, min value: " << bestValue << endl;
    }
    else {
        vector<int> valueList;
        vector<int> moveList = board.possibleMoves();
        for (size_t i=0; i < moveList.size(); i++) {
            Board newBoard = board;
            newBoard.addMove(moveList.at(i), 'O');
            cout << "min " << endl;
            cout << newBoard << endl;
            max(newBoard, possibleMove, possibleValue);
            possibleMove = moveList.at(i);
            cout << "possibleMove (min): " << possibleMove << endl;
            cout << "possibleValue (min): " << possibleValue << endl;

            valueList.push_back(possibleValue);
            if (possibleValue == -1) {
                // cout << "Exiting min early" << endl;
                break;
            }
        }
        int minValue = 1;
        int minValueIndex = 0;
        for (size_t i=0; i < valueList.size(); i++) {
            if (minValue > valueList.at(i)) {
                minValue = valueList.at(i);
                minValueIndex = i;
            }
        }
        // cout << "min: " << minValueIndex << endl;
        bestMove = moveList.at(minValueIndex);
        bestValue = minValue;
        cout << "bestMove: " << bestMove << " " << "bestValue: " << bestValue << endl;
    }
    return;
}
