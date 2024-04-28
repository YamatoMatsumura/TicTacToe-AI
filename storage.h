#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "board.h"

int getSaveFileCount();
void saveGame(int& nextSaveFileNum, const std::vector<char> BOARD_STATE, const int SAVE_FILE_COUNT, const char PLAYER);
void showSaveFiles(int fileCount);
void loadSaveFile(const int SAVE_FILE_NUM, Board& board, char& player);


#endif // STORAGE_H