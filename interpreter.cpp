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

#include "SDL/SDL.h"
#include "interpreter.h"
#include <iostream>

Interpreter::Interpreter() {

    int width, height, toWin, numPlayers;
    int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP;

    SCREEN_BPP = 32;

    screen = NULL;
    whiteSquare = NULL;
    blueSquare = NULL;
    redCircle = NULL;
    purpleCircle = NULL;
    greenCircle = NULL;
    yellowCircle = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);

    whiteSquare = loadImage("images/whiteSquare.bmp");
    blueSquare = loadImage("images/blueSquare.bmp");
    redCircle = loadImage("images/redCircle.bmp");
    purpleCircle = loadImage("images/purpleCircle.bmp");
    greenCircle = loadImage("images/greenCircle.bmp");
    yellowCircle = loadImage("images/yellowCircle.bmp");

    std::cout << "Enter the number of players (1-4): ";
    std::cin >> numPlayers;

    std::cout << "Enter the dimensions of the board: " << std::endl;
    std::cout << "Width: ";
    std::cin >> width;
    SCREEN_WIDTH = width*64;

    std::cout << "Height: ";
    std::cin >> height;
    SCREEN_HEIGHT = 64 + height*64;

    std::cout << "Number in a row to win: ";
    std::cin >> toWin;


    game = new Board(numPlayers, width, height, toWin, this);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Connect-Four", NULL);

    printGame();
}




void Interpreter::startGame() {
    char exec;
    bool gameWon = false;

    while (game->canPlay() && ! gameWon && exec != 'q') {
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

/*
 * Deletes the game and clears the screen
 */
Interpreter::~Interpreter() {
    delete game;
    SDL_FreeSurface(screen);
    SDL_Quit();
}

/*
 * Prints the board game and refreshes the screen window
 */
void Interpreter::printGame() {
    game->printBoard();
}

/*
 * Loads a screen to a SDL_Surface by filename
 */
SDL_Surface* Interpreter::loadImage(std::string filename) {
    // Temp storage for the image that's loaded
    SDL_Surface *loadedImage = NULL;

    SDL_Surface *optimizedImage = NULL;

    loadedImage = SDL_LoadBMP(filename.c_str());

    if (loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

/*
 * Applies a surface to another at (x,y)
 */
void Interpreter::applySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination) {
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

/*
 * Prints a tile to the game screen
 */
void Interpreter::applyTile(char tile, int x, int y) {
    //std::cout << "Attempting to place " << tile << " at ("<<x<<","<<y<<")" << std::endl;
    switch(tile) {
        case '-':
            applySurface(x, y, whiteSquare, screen);
            break;
        case ' ':
            applySurface(x, y, blueSquare, screen);
            break;
        case 'A':
            applySurface(x, y, blueSquare, screen);
            applySurface(x, y, redCircle, screen);
            break;
        case 'B':
            applySurface(x, y, blueSquare, screen);
            applySurface(x, y, greenCircle, screen);
            break;
        case 'C':
            applySurface(x, y, blueSquare, screen);
            applySurface(x, y, purpleCircle, screen);
            break;
        case 'D':
            applySurface(x, y, blueSquare, screen);
            applySurface(x, y, yellowCircle, screen);
            break;

    }
}
