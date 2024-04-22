#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include <vector>
#include <fstream>

int minimax(Board board);
void min(Board board, int& bestMove, int& bestValue);
void max(Board board, int& bestMove, int& bestValue);
void outputMove(std::ostream& out);

#endif // MINIMAX_H