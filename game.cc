
#include "tictactoe.h"
#include <iostream>
#include <regex>
#include <string>

Game::Game() : grid {'1', '2', '3', '4', '5', '6', '7', '8', '9'}
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
        "+---+---+---+\n";

    for (int row = 0 ; row < 3 ; row++) {
        for (int col = 0 ; col < 3 ; col++) {
            g[row * 28 + col * 4 + 16] = grid[3 * row + col];
        }
    }

    std::cout << g << std::flush;
}

int Game::input()
{
    std::string line;
    std::smatch sm;
    std::regex e {"\\s*([1-9])\\s*"};

    std::cout << "Your turn. You are " << player << ": " << std::flush;

    std::getline(std::cin, line);

    if (std::regex_match(line, sm, e)) {
        return std::stoi(sm[1]);
    }

    return 0;
}

bool Game::player_move()
{
    print_grid();

    for (int i = 0 ; i < 4 ; i++) {

        int move = input();

        if (move) {
            if (valid_move(move)) {
                grid[move - 1] = player;
                return false;
            }
            else {
                std::cout << "Invalid move." << std::endl;
            }

        }
        else {
            std::cout << "Invalid input. Try again." << std::endl;
        }
    }

    return true;
}

bool Game::valid_move(int move)
{
    if (1 <= move && move <= 9)
        return grid[move - 1] == '0' + move;

    return false;
}






