/*
 * =====================================================================================
 *
 *       Filename:  board.cpp
 *
 *    Description:  Board class for connect four
 *
 *         Author:  Jeff Dyck
 *
 * =====================================================================================
 */

//#include "piece.h"
#include "board.h"
#include <iostream>
#include <cstdio>

Board::Board(int numPlayers, int width, int height, int numToWin) {
    this->numPlayers = numPlayers;
    this->width = width;
    this->height = height + 1;  // +1 to account for top row to move piece
    this->grid = new char*[this->height];
    this->numToWin = numToWin;
    this->curPlayer = 1;
    this->curPieceCol = 0;
    this->curPieceType = curPlayer + 64;
    
    for (int i = 0; i < this->height; i++) {
        this->grid[i] = new char[this->width];
    }
    
    // Initializes each space to a blank char
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            grid[i][j] = ' ';
        }
    }

    // Denotes the height of each column
    // No pieces placed - height of 0 at each column
    colHeights.resize(this->width, 0);

    grid[0][0] = curPieceType;

}

/*
 * Deletes the board and its grid
 */
Board::~Board() {
    for (int i = 0; i < height; i++) {
        delete[] grid[i];
    }
    delete[] grid;

}



/*
 * Prints the board to stdout
 */
void Board::printBoard() {
    std::cout << "Current player: " << curPlayer << std::endl << std::endl;
    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for (int j = 0; j < width; j++) {
            std::cout << grid[i][j];
        }
        std::cout << "|" << std::endl;
    }
    for (int i = 0; i < width+2; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

/*
 * Returns true if at least one column can accept a piece
 */
bool Board::canPlay() {
    for (int i = 0; i < width; i++) {
        if (canDrop(i)) return true;
    }

    return false;
}


/*
 * Returns true if the specified column can accept another piece
 */
bool Board::canDrop(int col) {
    return (colHeights[col] < height-1);
}

/*
 * Sets the piece in the column to pieceType
 * Automatically calculates the correct height
 */
void Board::setPiece(int col, char pieceType) {
    grid[height - 1 - colHeights[col]][col] = pieceType;
    colHeights[col]++;
}

/*
 * Moves the piece left or right according to dir
 * Does nothing if out of range of the board
 */
void Board::movePiece(int dir) {
    if (curPieceCol + dir < width && curPieceCol + dir >= 0) {
        grid[0][curPieceCol] = ' ';
        curPieceCol += dir;
        grid[0][curPieceCol] = curPieceType;
    }
}

/*
 * Drops the piece based on the current player and column selected
 * Iterates curPlayer
 */
bool Board::dropPiece() {
    if (canDrop(curPieceCol)) {
        grid[0][curPieceCol] = ' ';
        setPiece(curPieceCol, curPieceType); 
        return true;
    }

    return false;

}

void Board::iteratePlayer() {
    if (curPlayer == numPlayers) curPlayer = 1;
    else curPlayer++;

    curPieceCol = 0;
    curPieceType = curPlayer+64;

    grid[0][0] = curPieceType;

}


bool Board::wonGame() {
    try {
    int inARow = 1;
    int x = curPieceCol;
    int y = height - colHeights[curPieceCol] ;

    int workX = x;
    int workY = y;

    // Check left/right pieces

        workX = x-1;

        // Left
        while (workX >= 0 && grid[workY][workX] == curPieceType) {
            workX--;
            inARow++;
        }

        // Right
        workX = x+1;

        while (workX < width && grid[workY][workX] == curPieceType) {
            workX++;
            inARow++;
        }

        if (inARow >= numToWin) return true;

    // Check pieces below
        workX = x;
        workY = y;
        inARow = 1;

        // Down
        while (workY < height-1 && grid[workY][workX] == curPieceType) {
            workY++;
            inARow++;
        }

        if (inARow >= numToWin) return true;

    // Check bottom-left/top-right diagonal pieces
        inARow = 1;
        workX = x-1;
        workY = y+1;

        // Left
        printf("workX: %d\n", workX);
        printf("workY: %d\n", workY);
        printf("height-1: %d\n", height-1);
        //printf("grid:: %c\n", grid[workY]);
        while (workX >= 0 && workY < height && grid[workY][workX] == curPieceType) {
            workX--;
            workY++;
            inARow++;
            std::cout << "inARow: " << inARow << std::endl;
        }
        workX = x+1;
        workY = y-1;


        // Right
        while (workX < width && workY >= 0 && grid[workY][workX] == curPieceType) {
            workX++;
            workY--;
            inARow++;
            std::cout << "inARow2: " << inARow << std::endl;
        }

        if (inARow >= numToWin) return true;

    // Check top-left/bottom-right diagonal pieces
        inARow = 1;
        workX = x-1;
        workY = y-1;

        // Left
        while (workX >= 0 && workY >= 0 && grid[workY][workX] == curPieceType) {
            workX--;
            workY--;
            inARow++;
        }
        workX = x+1;
        workY = y+1;

        // Right
        while (workX < width && workY < height && grid[workY][workX] == curPieceType) {
            workX++;
            workY++;
            inARow++;
        }

        if (inARow >= numToWin) return true;

    } catch(...) {
        std::cerr << "Problem in gameWon function. Fix pl0x" << std::endl;
    }


    // inARow never == numToWin, did not win
    return false;
}


/*
 * Returns the current player
 * This is only called when the game is won, hence the name
 */
int Board::winningPlayer() {
    return curPlayer;
}












