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

#include <iostream>
#include <vector>

class Board {
    char **grid;

    int width, height; 
    int numPlayers;
    int numToWin;
    int curPlayer;
    int curPieceCol;
    char curPieceType;

    std::vector<int> colHeights;

    void setPiece(int col, char pieceType);
    bool canDrop(int col);

    public:
        void movePiece(int dir);
        bool dropPiece();

        bool canPlay();
        bool wonGame();
        int winningPlayer();

        void iteratePlayer();

        void printBoard();

        Board(int numPlayers, int width, int height, int numToWin);
        ~Board();

};


#endif
