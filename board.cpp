// Author: Yamato Matsumura
// Assignment: Final Project

#include "board.h"
#include <vector>
#include <fstream>

using namespace std;

Board::Board() {
    const int BOARD_SIZE = 9;

    // Initialize empty board
    for (int i=0; i < BOARD_SIZE; i++) {
        _boardState.push_back('-');
    }
}

Board::Board(const vector<char> BOARD_STATE) {
    _boardState = BOARD_STATE;
}

Board::Board(const Board& OTHER) {
    const int BOARD_SIZE = 9;

    // Create a board copy
    _boardState.clear();
    for (int i=0; i < BOARD_SIZE; i++) {
        _boardState.push_back(OTHER.getBoardState().at(i));
    }
}

Board::~Board() {
    _boardState.clear();
}

void Board::restart() {
    const int BOARD_SIZE = 9;

    // Re-initialize an empty board
    _boardState.clear();
    for (int i=0; i < BOARD_SIZE; i++) {
        _boardState.push_back('-');
    }
}

vector<char> Board::getBoardState() const{
    return _boardState;
}

void Board::setBoardState(const vector<char> BOARD_STATE) {
    _boardState = BOARD_STATE;
}

bool Board::addMove(const int SQUARE, const char MOVE) {
    // Check if SQUARE is an empty space
    if (_boardState.at(SQUARE) != '-') {
        return false;
    }

    // Add move
    _boardState.erase(_boardState.begin() + SQUARE);
    _boardState.insert(_boardState.begin() + SQUARE, MOVE);

    return true;
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

    // Get all squares that aren't empty
    for (size_t i=0; i < _boardState.size(); i++) {
        if (_boardState.at(i) == '-') {
            moves.push_back(i);
        }
    }
    return moves;
}

bool Board::gameOver() const {
    // Check if someone won
    if (winner() != '-') {
        return true;
    }

    // Check for no remaining empty spaces left
    for (char item : _boardState) {
        if (item == '-') {
            return false;
        }
    }

    return true;
}

char Board::winner() const {
    const int ROW_COL_LEN = 3;
    char winPlayer = '-';

    // Check horizontal 3 in a row
    int startPos = 0;
    int endPos = 2; // Since 3x3 board
    char hWinTrack; // Becomes piece at starting index to check if all other pieces in that row are the same

    // Loop over each row
    for (int i=0; i < ROW_COL_LEN; i++) {
        hWinTrack = _boardState.at(startPos);
        bool horizontalWin = true;
        for (int j=startPos; j <= endPos; j++) {
            // If piece at starting index doesn't match piece in same row
            if (hWinTrack != _boardState.at(j)) {
                horizontalWin = false;
            }
        }
        startPos += ROW_COL_LEN;
        endPos += ROW_COL_LEN;

        if (horizontalWin && hWinTrack != '-') {
            winPlayer = hWinTrack;
        }
    }

    // Check vertical 3 in a row
    char vWinTrack; // Becomes piece at starting index to check if all other pieces in that col are the same

    // Loop over each col
    for (size_t i=0; i < ROW_COL_LEN; i++) {
        vWinTrack = _boardState.at(i);
        bool verticalWin = true;
        if (vWinTrack != _boardState.at(i+3) || vWinTrack != _boardState.at(i+6)) {
            verticalWin = false;
        }

        if (verticalWin && vWinTrack != '-') {
            winPlayer = vWinTrack;
        }
    }

    // Check diagnol 3 in a row
    char dWinTrack;
    vector<int> loopIndex = {0, 8, 2, 6}; // 0, 8 is top left and bottom right. 2, 6 is top right and bottom left

    // Loop over needed indexes in loopIndex
    for (size_t i=0; i < loopIndex.size(); i+= 2) {
        dWinTrack = _boardState.at(4);
        bool diagnolWin = true;
        if (dWinTrack != _boardState.at(loopIndex.at(i)) || dWinTrack != _boardState.at(loopIndex.at(i+1))) {
            diagnolWin = false;
        }

        if (diagnolWin && dWinTrack != '-') {
            winPlayer = dWinTrack;
        }
    }

    return winPlayer;
}

int Board::evaulateBoard() const {
    if (winner() == 'X') {
        return 1;
    }
    else if (winner() == 'O') {
        return -1;
    }
    else {
        return 0;
    }
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
