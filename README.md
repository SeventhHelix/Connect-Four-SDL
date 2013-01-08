Connect-Four SDL
================

Playing
-------

After running the executable, choose how many players you want to have, and enter the board size.

Controls:
    Left/Right          Move piece left and right
    Spacebar/Down       Drop piece

![Screenshot of gameplay](https://raw.github.com/SeventhHelix/Connect-Four-SDL/master/Screenshot.png "Screenshot")



Compiling and running
---------------------

To compile: 
    <blockquote>
    <p>$ make</p>
    </blockquote>

To clean up files after compilation:
    <blockquote>
    <p>$ make clean</p>
    </blockquote>

To run:
    <blockquote>
    <p>$ ./connectFour</p>
    </blockquote>

SDL
---

You will need the SDL library to compile this program
Instructions on how to get SDL, as well as some great tutorials on programming with SDL, can be found here: http://lazyfoo.net/SDL_tutorials/lesson01/index.php

Notes
-----

    The most common grid size is 7 wide, 6 high, with 4 in a row to win. This program does support arbitrary sizes, however.
    The window size will be scaled proportional to the width and height of the grid. Each piece is 64x64 px
    Small grids may cause the ending graphic to be cut off or displayed funny.
