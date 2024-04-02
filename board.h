#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream>

class Board {
    public:
        Board();
        Board(const std::vector<char> BOARD_STATE);
        std::vector<char> getBoardState() const;
        void addMove(const int SQUARE, const char MOVE);
        char currentPlayer() const;
        std::vector<int> possibleMoves() const;
        bool gameOver() const;
        char winner() const; // Only call if terminal
    private:
        std::vector<char> _boardState;
};

std::ostream& operator<<(std::ostream& out, const Board& BOARD);

#endif // BOARD_H