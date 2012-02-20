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

#include "interpreter.h"
#include <iostream>

Interpreter::Interpreter() {
    int width, height, toWin;
    std::cout << "Enter the dimensions of the board: " << std::endl;
    std::cout << "Width: ";
    std::cin >> width;
    std::cout << "Height: ";
    std::cin >> height;
    std::cout << "Number in a row to win: ";
    std::cin >> toWin;
    game = new Board(width, height, toWin);
}

Interpreter::~Interpreter() {
    delete game;
}

void Interpreter::printGame() {
    game->printBoard();
}
