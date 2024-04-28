#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "board.h"

/**
 * @brief Get number of save files in saveFiles folder
 * 
 * @return int 
 */
int getSaveFileCount();
/**
 * @brief Saves current board state by writing it to a txt file in saveFiles folder
 * 
 * @param nextSaveFileNum - Save file number so each save file has a unique name
 * @param BOARD_STATE - Current board state
 * @param SAVE_FILE_COUNT - Total number of save files in saveFiles folder
 * @param PLAYER 
 */
void saveGame(int& nextSaveFileNum, const std::vector<char> BOARD_STATE, const int SAVE_FILE_COUNT, const char PLAYER);
/**
 * @brief Displays all save files in terminal
 * 
 * @param fileCount - Total number of save files in saveFiles folder
 */
void showSaveFiles(int fileCount);
/**
 * @brief Loads chosen save file into current game
 * 
 * @param SAVE_FILE_NUM - Save file number to load
 * @param board - Current board
 * @param player - If in game being loaded, player is X or O
 */
void loadSaveFile(const int SAVE_FILE_NUM, Board& board, char& player);


#endif // STORAGE_H