#ifndef AI_H
#define AI_H

#include "board.h"
#include <vector>
#include <fstream>

class AI {
    public:
        int evaulateBoard(const Board board);
        std::vector<int> minimax();
        std::vector<int> min();
        std::vector<int> max();
        void outputMove(std::ostream& out);
};

#endif // AI_H