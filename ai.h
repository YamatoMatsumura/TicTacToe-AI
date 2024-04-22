#ifndef AI_H
#define AI_H

#include "board.h"
#include <vector>
#include <fstream>

int evaulateBoard(const Board BOARD);  // Only call on terminal
int minimax(Board board);
void min(Board board, int& bestMove, int& bestValue);
void max(Board board, int& bestMove, int& bestValue);
void outputMove(std::ostream& out);

#endif // AI_H