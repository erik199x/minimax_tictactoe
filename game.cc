
#include "tictactoe.h"
#include <string.h>
#include <iostream>
#include <climits>
#include <regex>
#include <string>

Game::Game() : grid {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
{
    player = 'O';
    computer = 'X';
    turn = computer;
    computer_win = false;
    score_computer = 0;
    depth_zero_move = 0;
}

void Game::print_grid()
{
    char g[] =
        "+---+---+---+    +---+---+---+\n"
        "|   |   |   |    | 1 | 2 | 3 |\n"
        "+---+---+---+    +---+---+---+\n"
        "|   |   |   |    | 4 | 5 | 6 |\n"
        "+---+---+---+    +---+---+---+\n"
        "|   |   |   |    | 7 | 8 | 9 |\n"
        "+---+---+---+    +---+---+---+\n";

    for (int row = 0 ; row < 3 ; row++)
        for (int col = 0 ; col < 3 ; col++)
            g[row * 62 + col * 4 + 33] = grid[3 * row + col];

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

        int move = input() - 1;

        if (!set(move, player))
            return false;
        else
            std::cout << "Invalid move." << std::endl;
    }

    return true;
}

bool Game::set(int i, char c)
{
    if (0 <= i && i < 9 && grid[i] == ' ') {
        grid[i] = c;
        return false;
    }
    else
        return true;
}

bool Game::reset(int i)
{
    if (0 <= i && i < 9) {
        grid[i] = ' ';
        return false;
    }
    else
        return true;
}

int Game::minimax(int depth, bool max, int prev_move)
{
    if (check_win(prev_move))
        return max ? -1 : 10 - depth;

    if (depth == 9)
        return 0;

    if (max) {
        int value = INT_MIN;

        for (int i = 0 ; i < 9 ; i++) {
            if (!set(i, computer)) {
                value = std::max(value, minimax(depth + 1, false, i));
                reset(i);
            }
        }

        return value;
    }
    else {
        int value = INT_MAX;

        for (int i = 1 ; i < 9 ; i++) {
            if (!set(i, player)) {
                value = std::min(value, minimax(depth + 1, true, i));
                reset(i);
            }
        }

        return value;
    }
}

bool Game::check_win(int prev_move)
{
    switch (prev_move) {
        case 0:
            return equal_row(0) || equal_col(0) || equal_back_slash();
        case 1:
            return equal_row(0) || equal_col(1);
        case 2:
            return equal_row(0) || equal_col(2) || equal_forward_slash();
        case 3:
            return equal_row(1) || equal_col(0);
        case 4:
            return equal_row(1) || equal_col(1) || equal_back_slash() || equal_forward_slash();
        case 5:
            return equal_row(1) || equal_col(2);
        case 6:
            return equal_row(2) || equal_col(0) || equal_forward_slash();
        case 7:
            return equal_row(2) || equal_col(1);
        case 8:
            return equal_row(2) || equal_col(2) || equal_back_slash();
    }

    return false;
}

bool Game::equal_row(int i)
{
    return grid[3*i] == grid[3*i + 1] && grid[3*i] == grid[3*i + 2];
}

bool Game::equal_col(int i)
{
    return grid[i] == grid[i+3] && grid[i] == grid[i+6];
}

bool Game::equal_back_slash()
{
    return grid[0] == grid[4] && grid[4] == grid[8];
}

bool Game::equal_forward_slash()
{
    return grid[2] == grid[4] && grid[2] == grid[6];
}

int Game::computer_move(int depth)
{
    if (depth == 0) {
        set(depth_zero_move, computer);
        return depth_zero_move;
    }

    int best_move = -1;
    int best_value = INT_MIN;

    for (int i = 0 ; i < 9 ; i++)
        if (!set(i, computer)) {
            int value = minimax(depth + 1, false, i);
            reset(i);

            if (value > best_value) {
                best_move = i;
                best_value = value;
            }
        }

    set(best_move, computer);

    return best_move;
}

void Game::print_score()
{
    std::cout << "You: 0\nComputer: " << score_computer << std::endl;
}

void Game::start()
{
    while (true) {
        for (int depth = 0 ; depth < 9 ; depth++) {
            if (next_move(depth))
                return;

            if (computer_win)
                break;
        }

        print_grid();
        if (computer_win)
            std::cout << "Game over. You have lost!" << std::endl;
        else
            std::cout << "It's a draw!" << std::endl;

        print_score();

        if (play_again())
            reset();
        else
            return;
    }
}

bool Game::next_move(int depth)
{
    if (turn == player) {
        if (player_move())
            return true;

        turn = computer;
        return false;
    }

    if (check_win(computer_move(depth))) {
        computer_win = true;
        score_computer++;
    }

    turn = player;
    return false;
}

bool Game::play_again()
{
    std::string line;
    std::smatch sm;
    std::regex e {"\\s*(y|Y|yes|Yes|YES)\\s*"};

    std::cout << "Play again? [y/n]: " << std::flush;

    std::getline(std::cin, line);

    return std::regex_match(line, sm, e);
}

void Game::reset()
{
    memcpy(grid, "         ", 9);

    char tmp = player;
    player = computer;
    computer = tmp;
    turn = 'X';
    computer_win = false;

    if (turn == computer)
        depth_zero_move = (depth_zero_move == 0) ? 4 : 0;
}





