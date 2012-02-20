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

Board::Board(int width, int height, int numToWin) {
    this->width = width;
    this->height = height + 1;  // +1 to account for top row to move piece
    //this->pieces = new Piece[width][height + 1];
    this->grid = new char*[this->height];
    
    for (int i = 0; i < this->height; i++) {
        this->grid[i] = new char[this->width];
    }
    
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            grid[i][j] = ' ';
        }
    }

}

Board::~Board() {
    /*
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete pieces[i][j];
        }
    }
    */

}

/*
 * Prints the board to stdout
 */
void Board::printBoard() {
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
