#pragma once

#include "config.h"
#include "board.h"
#include "pieces.h"
#include "nn.h"

typedef struct {
    int rotation;
    int x;
    int y;           // Final drop y position
    double value;    // Predicted value: reward + _gamma * Q
    int lines_cleared;
    int resulting_board[HEIGHT][WIDTH];
} Action;

int generate_actions(Piece piece, Action actions[], int max_actions);
void animate_fall(Piece piece, int rotation, int x, int final_y, int saved_board[HEIGHT][WIDTH]);
int run_episode(void);

void update_best_checkpoint(int score, int episode);
void check_best_performance_and_restore(int score);