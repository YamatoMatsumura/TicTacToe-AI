#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream> // Not used yet

class Board {
    public:
        Board();
        Board(const std::vector<char> BOARD_STATE);
        Board(const Board& OTHER);
        ~Board();
        void restart();
        std::vector<char> getBoardState() const;
        void setBoardState(const std::vector<char> BOARD_STATE);
        bool addMove(const int SQUARE, const char MOVE);
        char currentPlayer() const;
        std::vector<int> possibleMoves() const;
        bool gameOver() const;
        char winner() const;
        int evaulateBoard() const;  // Only call on terminal
        Board& operator=(const Board& OTHER);

    private:
        std::vector<char> _boardState;
};

std::ostream& operator<<(std::ostream& out, const Board& BOARD); // For testing, can delete

#endif // BOARD_H