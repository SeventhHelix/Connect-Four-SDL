/*
 * =====================================================================================
 *
 *       Filename:  interpreter.cpp
 *
 *    Description:  Interpreter class - Link between user interaction and game
 *
 *         Author:  Jeff Dyck
 *
 * =====================================================================================
 */

#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "board.h"
class Board;
class Interpreter {
    Board *game;

    public:
        void movePiece(char dir);
        void dropPiece();
        bool gameWon();

        Interpreter();
        ~Interpreter();

        void printGame();

};


#endif


