
#ifndef TICTACTOE_H
#define TICTACTOE_H

class Game {

    public:
        char grid[9];
        char player;
        char computer;
        char turn;

        bool computer_win;
        int score_computer;
        int depth_zero_move;

        Game();
        void print_grid();
        int input();
        bool player_move();

        bool set(int i, char c);
        bool reset(int i);

        int minimax(int depth, bool max, int prev_move);
        bool check_win(int prev_move);
        bool equal_row(int i);
        bool equal_col(int i);
        bool equal_back_slash();
        bool equal_forward_slash();
        int computer_move(int depth);

        void print_score();

        void start();
        bool next_move(int depth);
        bool play_again();
        void reset();
};

#endif




