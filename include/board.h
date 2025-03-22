#pragma once

#include "config.h"

extern int board[HEIGHT][WIDTH];

void copy_board(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH]);
void print_board_custom(int board_state[HEIGHT][WIDTH]);
int check_collision(int b[HEIGHT][WIDTH], int piece[4][4], int x, int y);
void place_piece_on_board(int b[HEIGHT][WIDTH], int piece[4][4], int x, int y);
int clear_lines(int b[HEIGHT][WIDTH]);
int drop_piece(int b[HEIGHT][WIDTH], int piece[4][4], int x, int start_y);