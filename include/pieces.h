#pragma once

#include "config.h"

typedef struct {
    int rotations;         // Number of available rotations
    int shapes[4][4][4];   // Each rotation stored in a 4x4 grid
    int size;
} Piece;

extern Piece pieces[NUM_PIECES];

void init_pieces(void);