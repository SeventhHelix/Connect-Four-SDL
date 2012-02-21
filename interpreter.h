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
#include "SDL/SDL.h"

class Board;
class Interpreter {
    Board *game;
    int width, height, toWin, numPlayers;
    int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP;

    SDL_Surface *screen;
    SDL_Surface *whiteSquare;
    SDL_Surface *whiteCircle;
    SDL_Surface *blueSquareW;
    SDL_Surface *blueSquareB;
    SDL_Surface *redCircleW;
    SDL_Surface *redCircleB;
    SDL_Surface *purpleCircleW;
    SDL_Surface *purpleCircleB;
    SDL_Surface *greenCircleW;
    SDL_Surface *greenCircleB;
    SDL_Surface *yellowCircleW;
    SDL_Surface *yellowCircleB;

    public:
        void movePiece(char dir);
        void dropPiece();
        bool gameWon();

        Interpreter();
        ~Interpreter();
        void startGame();

        void printGame();

        SDL_Surface *loadImage(std::string filename);
        void applySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
        void applyTile(char tile, int x, int y);

};


#endif


