/*
 * =====================================================================================
 *
 *       Filename:  connectFour.cpp
 *
 *    Description:  Main file for Connect Four game
 *
 *         Author:  Jeff Dyc
 *
 * =====================================================================================
 */

#include <iostream>
//#include "piece.h"
#include "board.h"
#include "interpreter.h"

using namespace std;

int main() {
    Interpreter *intrp = new Interpreter;
    intrp->printGame();


    return 0;
}
