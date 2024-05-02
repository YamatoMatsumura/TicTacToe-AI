#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream>

class Board {
    public:
        /**
         * @brief Construct a new Board object
         * 
         */
        Board();

        /**
         * @brief Construct a new Board object
         * 
         * @param BOARD_STATE
         */
        Board(const std::vector<char> BOARD_STATE);

        /**
         * @brief Construct a new Board object
         * 
         * @param OTHER 
         */
        Board(const Board& OTHER);

        /**
         * @brief Destroy the Board object
         * 
         */
        ~Board();

        /**
         * @brief Re-initialize an empty board state
         * 
         */
        void restart();

        /**
         * @brief Get the Board State object
         * 
         * @return std::vector<char> 
         */
        std::vector<char> getBoardState() const;

        /**
         * @brief Set the Board State object
         * 
         * @param BOARD_STATE 
         */
        void setBoardState(const std::vector<char> BOARD_STATE);

        /**
         * @brief Add a move to board state
         * 
         * @param SQUARE Square on board to add move to
         * @param MOVE Move being made. Either X or O
         * @return true - Move succesfully added
         * @return false - Invalid move
         */
        bool addMove(const int SQUARE, const char MOVE);

        /**
         * @brief Returns whos turn it is next
         * 
         * @return char - X or O
         */
        char currentPlayer() const;

        /**
         * @brief Gets all possible moves that can be made
         * 
         * @return std::vector<int> - Indxe of available move
         */
        std::vector<int> possibleMoves() const;

        /**
         * @brief Checks if game is over
         * 
         * @return true 
         * @return false 
         */
        bool gameOver() const;

        /**
         * @brief Returns who won the game
         * 
         * @return char 
         */
        char winner() const;

        /**
         * @brief Assignts int value to current board
         * 
         * @return int - 1 if x won, -1 is o won, 0 if tie
         */
        int evaulateBoard() const;  // Only call on terminal

        /**
         * @brief Copy assignment operator
         * 
         * @param OTHER 
         * @return Board& 
         */
        Board& operator=(const Board& OTHER);
    private:
        std::vector<char> _boardState;
};
std::ostream& operator<<(std::ostream& out, const Board& BOARD); // For testing, can delete

#endif // BOARD_H