#include "board.h"
#include <vector>
#include <fstream>
#include <iostream> // Testing, delete later

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

Board::~Board() {
    _boardState.clear();
}

Board::Board(const Board& OTHER) {
    _boardState.clear();
    for (int i=0; i < 9; i++) {
        _boardState.push_back(OTHER.getBoardState().at(i));
    }
}

vector<char> Board::getBoardState() const{
    return _boardState;
}

void Board::setBoardState(const vector<char> BOARD_STATE) {
    _boardState = BOARD_STATE;
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
    if (winner() != '-') {
        return true;
    }
    for (char item : _boardState) {
        if (item == '-') {
            return false;
        }
    }
    return true;
}

char Board::winner() const {
    char winPlayer = '-';

    // Check horizontal 3 in a row
    int startPos = 0;
    int endPos = 2;
    char hWinTrack;
    for (int i=0; i < 3; i++) {
        hWinTrack = _boardState.at(startPos);
        bool horizontalWin = true;
        for (int j=startPos; j <= endPos; j++) {
            if (hWinTrack != _boardState.at(j)) {
                horizontalWin = false;
            }
        }
        startPos += 3;
        endPos += 3;

        if (horizontalWin) {
            winPlayer = hWinTrack;
        }
    }

    // Check vertical 3 in a row
    char vWinCheck;
    for (size_t i=0; i < _boardState.size() / 3; i++) {
        vWinCheck = _boardState.at(i);
        bool verticalWin = true;
        if (vWinCheck != _boardState.at(i+3) || vWinCheck != _boardState.at(i+6)) {
            verticalWin = false;
        }

        if (verticalWin) {
            winPlayer = vWinCheck;
        }
    }

    // Check diagnol 3 in a row
    char dWinCheck;
    vector<int> loopIndex = {0, 8, 2, 6};
    for (size_t i=0; i < loopIndex.size(); i+= 2) {
        dWinCheck = _boardState.at(4);
        bool diagnolWin = true;
        if (dWinCheck != _boardState.at(loopIndex.at(i)) || dWinCheck != _boardState.at(loopIndex.at(i+1))) {
            diagnolWin = false;
        }

        if (diagnolWin) {
            winPlayer = dWinCheck;
        }
    }

    return winPlayer;
}

int Board::getClickedSquare(const int X, const int Y) {
    const int WINDOW_WIDTH = 690;
    const int SQUARE_WIDTH = 230;
    int column = 0;
    int row = 0;
    for (int i=SQUARE_WIDTH; i <= 690; i+= SQUARE_WIDTH) {
        if (X > i) {
            column += 1;
        }

        if (Y > i) {
            row += 1;
        }
    }

    // Get index of board vector from row & column
    int index = row * 3 + column;
    return index;
}

Board& Board::operator=(const Board& OTHER) {
    if (this == &OTHER) {
        return *this;
    }

    for (size_t i=0; i < this->_boardState.size(); i++) {
        this->_boardState.at(i) = OTHER._boardState.at(i);
    }
    return *this;
}


ostream& operator<<(std::ostream& out, const Board& BOARD) {
    vector<char> boardState = BOARD.getBoardState();
    for (size_t i=0; i < boardState.size(); i+=3) {
        out << boardState.at(i) << '|' << boardState.at(i+1) << '|' << boardState.at(i+2) << endl;
    }
    return out;
}
