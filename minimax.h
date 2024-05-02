// Author: Yamato Matsumura
// Assignment: Final Project

#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include <vector>
#include <fstream>

/**
 * @brief Finds the best value with given board state
 * 
 * @param board - Current board
 * @return int - Index of best move
 */
int minimax(Board board);

/**
 * @brief Finds best move for O
 * 
 * @param board - Current board
 * @param bestMove - Index of best move
 * @param bestValue - Value rating of best move. -1 if X winning, 1 if O winning, 0 if tie
 */
void min(Board board, int& bestMove, int& bestValue);

/**
 * @brief Finds best move for X
 * 
 * @param board - Current board
 * @param bestMove - Index of best move
 * @param bestValue - Value rating of best move. -1 is X winning, 1 if O winning, 0 if tie
 */
void max(Board board, int& bestMove, int& bestValue);


#endif // MINIMAX_H