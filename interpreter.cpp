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
    int width, height, toWin, numPlayers;
    std::cout << "Instructions: r->right, l->left, d->drop" << std::endl;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;
    std::cout << "Enter the dimensions of the board: " << std::endl;
    std::cout << "Width: ";
    std::cin >> width;
    std::cout << "Height: ";
    std::cin >> height;
    std::cout << "Number in a row to win: ";
    std::cin >> toWin;
    game = new Board(numPlayers, width, height, toWin);
    printGame();

    char exec;
    bool gameWon = false;

    while (game->canPlay() && ! gameWon) {
        std::cin >> exec;
        switch(exec) {
            case 'l':
                game->movePiece(-1); break;
            case 'r':
                game->movePiece(1); break;
            case 'd':
                if (game->dropPiece()) {
                    if (game->wonGame()) gameWon = true;
                    else game->iteratePlayer();
                }
                break;
        }

        printGame();
    }

    if (gameWon) {
        std::cout << "Player " << game->winningPlayer() << " wins!" << std::endl;
    } else {
        std::cout << "Well that was boring. Nobody won the game." << std::endl;
    }

}

Interpreter::~Interpreter() {
    delete game;
}

void Interpreter::printGame() {
    game->printBoard();
}
