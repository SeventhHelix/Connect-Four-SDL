/*
 * =====================================================================================
 *
 *       Filename:  board.h
 *
 *    Description:  Board class for connect four
 *
 *         Author:  Jeff Dyck
 *
 * =====================================================================================
 */

#ifndef __BOARD_H__
#define __BOARD_H__

//#include "piece.h"
#include <iostream>

class Board {
    //Piece ***pieces;
    //Piece *activePiece;

    char **grid;

    int width, height;

    bool checkWin();
    
    public:
        void moveLeft();
        void moveRight();
        void dropPiece();

        bool canMove();
        void printBoard();

        Board(int width, int height, int numToWin);
        ~Board();
    
};


#endif
