
#include "tictactoe.h"
#include <stdlib.h>

int main()
{
    Game g = Game();

    g.player = 'X';

    for (int i = 0 ; i < 9 ; i++)
        g.player_move();

    return EXIT_FAILURE;
}




