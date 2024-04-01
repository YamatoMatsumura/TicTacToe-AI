#include "board.h"
#include <vector>
#include <fstream>

using namespace std;

Board::Board() {
    vector<char> boardState;
    for (int i=0; i < 9; i++) {
        boardState.push_back('-');
    }
    _boardState = boardState;
}

Board::Board(const vector<char> BOARD_STATE) {
    _boardState = BOARD_STATE;
}

vector<char> Board::getBoardState() const{
    return _boardState;
}

void Board::addMove(const int SQUARE, const char MOVE) {
    _boardState.erase(_boardState.begin() + SQUARE);
    _boardState.insert(_boardState.begin() + SQUARE, MOVE);
}

char Board::currentPlayer() const {
    int XCount = 0;
    int YCount = 0;
    // Count number of X and O in board
    for (char item : _boardState) {
        if (item == 'X') {
            XCount += 1;
        }
        else if (item == 'O') {
            YCount += 1;
        }
    }


    if (XCount > YCount) {
        return 'O';
    }
    else {
        return 'X';
    }
}

vector<int> Board::possibleMoves() const {
    vector<int> moves;
    for (size_t i=0; i < _boardState.size(); i++) {
        if (_boardState.at(i) == '-') {
            moves.push_back(i);
        }
    }
    return moves;
}

bool Board::gameOver() const {
    for (char item : _boardState) {
        if (item == '-') {
            return false;
        }
    }
    return true;
}

char Board::winner() const {
    bool winnerStatus = true;

    // Check horizontal 3 in a row
    int startPos = 0;
    int endPos = 2;
    for (int i=0; i < 3; i++) {
        char firstElement = _boardState.at(startPos);
        for (int j=startPos; j <= endPos; j++) {
            if (firstElement != _boardState.at(i)) {
                winnerStatus = false;
            }
        }
        startPos += 3;
        endPos += 3;
    }

    // Check vertical 3 in a row
    for (size_t i=0; i < _boardState.size() / 3; i++) {
        char firstElement = _boardState.at(i);
        if (firstElement != _boardState.at(i+3) || firstElement != _boardState.at(i+6)) {
            winnerStatus = false;
        }
    }

    // Check diagnol 3 in a row
    vector<int> loopIndex = {0, 8, 2, 6};
    for (size_t i=0; i < loopIndex.size(); i+= 2) {
        char middleElement = _boardState.at(4);
        if (middleElement != _boardState.at(i) || middleElement != _boardState.at(i+1)) {
            winnerStatus = false;
        }
    }
    return winnerStatus;
}


ostream& operator<<(std::ostream& out, const Board& BOARD) {
    vector<char> boardState = BOARD.getBoardState();
    for (size_t i=0; i < boardState.size(); i+=3) {
        out << boardState.at(i) << '|' << boardState.at(i+1) << '|' << boardState.at(i+2) << endl;
    }
    return out;
}
