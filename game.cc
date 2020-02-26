
#include "tictactoe.h"
#include <iostream>

Game::Game() : grid {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
{

}

void Game::print_grid()
{
    char g[] =
        "+---+---+---+\n"
        "|   |   |   |\n"
        "+---+---+---+\n"
        "|   |   |   |\n"
        "+---+---+---+\n"
        "|   |   |   |\n"
        "+---+---+---+";

    for (int row = 0 ; row < 3 ; row++) {
        for (int col = 0 ; col < 3 ; col++) {
            g[row * 28 + col * 4 + 16] = grid[3 * row + col];
        }
    }

    std::cout << g << std::endl;
}




