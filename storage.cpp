#include <fstream>

#include <iostream>
#include <string>
#include <vector>
using namespace std;


#include "storage.h"
using namespace std;

int getSaveFileCount() {
    int saveCount = 1; // Starts at saveFile1
    int fileCount = 0;

    while (true) {
        ifstream file("saveFiles/saveFile" + to_string(saveCount) + ".txt");

        // If file doesn't exist, break
        if (file.fail()) {
            break;
        }
        // Update counts
        fileCount += 1;
        saveCount += 1;
    }
    return fileCount;
}

void saveGame(int& nextSaveFileNum, const vector<char> BOARD_STATE, const int SAVE_FILE_COUNT, const char PLAYER) {
    // Check if at max file count
    const int MAX_FILE_COUNT = 9;
    if (SAVE_FILE_COUNT == MAX_FILE_COUNT) {
        cout << "Maximum Number of Save Files Reached." << endl;
        return;
    }

    ofstream out("saveFiles/saveFile" + to_string(nextSaveFileNum) + ".txt");

    for (size_t i=0; i < BOARD_STATE.size(); i+=3) {
        out << BOARD_STATE.at(i) << '|' << BOARD_STATE.at(i+1) << '|' << BOARD_STATE.at(i+2) << endl;
    }

    // Add player at bottom
    out << PLAYER << endl;

    nextSaveFileNum += 1;
}

void showSaveFiles(int fileCount) {
    const int DISPLAY_COUNT = 5; // Number of boards to display in each line

    // Load save file menu text
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "|   Choose Save File to Load   |" << endl; 
    cout << "|Press L to exit save file menu|" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    // Store each seperate line
    string outputLines[4];
    for (int i=1; i <= fileCount; i++) {
        ifstream file("saveFiles/saveFile" + to_string(i) + ".txt");

        // Sanity check file open
        if (file.fail()) {
            cerr << "File open fail" << endl;
        }


        outputLines[0] += to_string(i) + "." + "       ";
        string line;
        // Get each line and store in seperate string
        for (int j=1; j < 4; j++) {
            getline(file, line);
            outputLines[j] += line + "    ";
        }

        // If display count reached, display lines
        if (i % DISPLAY_COUNT == 0 || i == fileCount) {
            for (int j=0; j < 4; j++) {
                // Add space before first board for visual clarity
                if (j == 0) {
                    cout << outputLines[j] << endl;
                }
                else {
                    cout << " " + outputLines[j] << endl;
                }
            }
            cout << endl;

            // Reset outputLines array
            for (int j=0; j < 4; j++) {
                outputLines[j] = "";
            }
        }

    }
}

void loadSaveFile(const int SAVE_FILE_NUM, Board& board, char& player) {
    ifstream file("saveFiles/saveFile" + to_string(SAVE_FILE_NUM) + ".txt");

    const int BOARD_CHAR_NUM = 15; // Makes sure player piece data doesn't get copied into board state
    int charCount = 0;
    char nextChar;
    vector<char> newBoardState;
    while (file >> nextChar) {
        // If done copying board state
        if (charCount == BOARD_CHAR_NUM) {
            // Account for which piece player was in this save file
            player = nextChar;
        }

        // Copy board state
        if (nextChar == 'O' || nextChar == 'X' || nextChar == '-') {
            newBoardState.push_back(nextChar);
        }
        charCount += 1;
    }

    // Copy new board into old board
    Board newBoard(newBoardState);
    board = newBoard;

    cout << "Loading save file..." << endl;
}