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

    SDL_Init(SDL_INIT_EVERYTHING);

    whiteSquare = SDL_LoadBMP("images/whiteSquare.bmp");
    whiteCircle = SDL_LoadBMP("images/whiteCircleBlue.bmp");
    blueSquareW = SDL_LoadBMP("images/blueSquareWhite.bmp");
    blueSquareB = SDL_LoadBMP("images/blueSquareBlue.bmp");
    redCircleW = SDL_LoadBMP("images/redCircleWhite.bmp");
    redCircleB = SDL_LoadBMP("images/redCircleBlue.bmp");
    purpleCircleW = SDL_LoadBMP("images/purpleCircleWhite.bmp");
    purpleCircleB = SDL_LoadBMP("images/purpleCircleBlue.bmp");
    greenCircleW = SDL_LoadBMP("images/greenCircleWhite.bmp");
    greenCircleB = SDL_LoadBMP("images/greenCircleBlue.bmp");
    yellowCircleW = SDL_LoadBMP("images/yellowCircleWhite.bmp");
    yellowCircleB = SDL_LoadBMP("images/yellowCircleBlue.bmp");


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




/*
 * Starts and runs the main game
 */
void Interpreter::startGame() {
    char exec;
    bool gameWon = false;
    bool appliedEndGame = false;
    bool quit = false;
    SDL_Event event;

    while (quit == false && game->canPlay() && ! gameWon) { 
        if (SDL_PollEvent(&event)) {

            switch(event.type) {

                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:

                    switch(event.key.keysym.sym) {
                        J
                        case SDLK_LEFT:
                            game->movePiece(-1);
                            break;

                        case SDLK_RIGHT:
                            game->movePiece(1);
                            break;

                        case SDLK_SPACE:
                        case SDLK_DOWN:
                            if (game->dropPiece()) {
                                if (game->wonGame()) gameWon = true;
                                else game->iteratePlayer();
                            }
                            break;
                    }

                    printGame();
            }
        }
    }

    while (quit == false) {

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        if (! appliedEndGame) {
            std::cout << "applying end game" << std::endl;
            endGameApply();
            appliedEndGame = true;
        }
    }

    if (gameWon == true) {
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
    SDL_Flip(screen);
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
        // This line causes problems for some reason
        // Defeats the whole purpose of this function
        //optimizedImage = SDL_DisplayFormat(loadedImage);
        optimizedImage = loadedImage;
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
void Interpreter::applyTile(char tile, int xSmall, int ySmall) {
    //std::cout << "Attempting to place " << tile << " at ("<<x<<","<<y<<")" << std::endl;
    int x = xSmall*64;
    int y = ySmall*64;
    switch(tile) {
        case '-':
            applySurface(x, y, whiteSquare, screen);
            break;
        case ' ':
            applySurface(x, y, whiteCircle, screen);
            break;

        case 'A':
            applySurface(x, y, redCircleB, screen);
            break;
        case 'a':
            applySurface(x, y, redCircleW, screen);
            break;

        case 'B':
            applySurface(x, y, greenCircleB, screen);
            break;
        case 'b':
            applySurface(x, y, greenCircleW, screen);
            break;

        case 'C':
            applySurface(x, y, purpleCircleB, screen);
            break;
        case 'c':
            applySurface(x, y, purpleCircleW, screen);
            break;

        case 'D':
            applySurface(x, y, yellowCircleB, screen);
            break;
        case 'd':
            applySurface(x, y, yellowCircleW, screen);
            break;

    }
}

/*
 * Applies the endgame banner at the top according to the winning player
 */
void Interpreter::endGameApply() {
    int winningPlayer = game->winningPlayer();

    if (! game->wonGame()) {
        endGame = SDL_LoadBMP("images/tieGame.bmp");
    } else {
        switch(winningPlayer) {
            case 1:
                endGame = SDL_LoadBMP("images/playerOneWin.bmp");
                break;
            case 2:
                endGame = SDL_LoadBMP("images/playerTwoWin.bmp");
                break;
            case 3:
                endGame = SDL_LoadBMP("images/playerThreeWin.bmp");
                break;
            case 4:
                endGame = SDL_LoadBMP("images/playerFourWin.bmp");
                break;
            
        }

    }

    applySurface(1, 0, endGame, screen);

    SDL_Flip(screen);
}
