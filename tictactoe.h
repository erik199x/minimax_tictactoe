
#ifndef TICTACTOE_H
#define TICTACTOE_H

class Game {

    public:
        char grid[9];
        char player;
        char computer;

        Game();
        void print_grid();
        int input();
        bool player_move();
        bool valid_move(int move);

        int minimax(int depth, bool max, int prev_move);
        bool check_win(int prev_move);
};

#endif




