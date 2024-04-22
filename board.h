#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream>

class Board {
    public:
        Board();
        Board(const std::vector<char> BOARD_STATE);
        Board(const Board& OTHER);
        ~Board();
        std::vector<char> getBoardState() const;
        void setBoardState(const std::vector<char> BOARD_STATE);
        void addMove(const int SQUARE, const char MOVE);
        char currentPlayer() const;
        std::vector<int> possibleMoves() const;
        bool gameOver() const;
        char winner() const;
        int evaulateBoard() const;  // Only call on terminal
        int getClickedSquare(const int X, const int Y);
        Board& operator=(const Board& OTHER);

    private:
        std::vector<char> _boardState;
};

std::ostream& operator<<(std::ostream& out, const Board& BOARD);

#endif // BOARD_H