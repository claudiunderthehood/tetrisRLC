#include "board.h"

int board[HEIGHT][WIDTH];

void copy_board(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH]){
    int i, j;
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            dest[i][j] = src[i][j];
        }
    }
}

void print_board_custom(int board_state[HEIGHT][WIDTH]){
    int i, j;
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            if(board_state[i][j] == 1)
                printf("#");
            else if(board_state[i][j] == 2)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

int check_collision(int b[HEIGHT][WIDTH], int piece[4][4], int x, int y){
    int i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(piece[i][j]) {
                int bx = x + j;
                int by = y + i;
                if(bx < 0 || bx >= WIDTH || by < 0 || by >= HEIGHT)
                    return 1;
                if(b[by][bx] == 1)
                    return 1;
            }
        }
    }
    return 0;
}

void place_piece_on_board(int b[HEIGHT][WIDTH], int piece[4][4], int x, int y){
    int i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(piece[i][j]){
                int bx = x + j;
                int by = y + i;
                if(bx >= 0 && bx < WIDTH && by >= 0 && by < HEIGHT)
                    b[by][bx] = 1;
            }
        }
    }
}

int clear_lines(int b[HEIGHT][WIDTH]){
    int i, j, lines = 0;
    for(i = HEIGHT - 1; i >= 0; i--){
        int full = 1;
        for(j = 0; j < WIDTH; j++){
            if(b[i][j] != 1){
                full = 0;
                break;
            }
        }
        if(full){
            lines++;
            int k, l;
            for(k = i; k > 0; k--){
                for(l = 0; l < WIDTH; l++){
                    b[k][l] = b[k-1][l];
                }
            }
            for(j = 0; j < WIDTH; j++){
                b[0][j] = 0;
            }
            i++;
        }
    }
    return lines;
}

int drop_piece(int b[HEIGHT][WIDTH], int piece[4][4], int x, int start_y){
    int y = start_y;
    while(!check_collision(b, piece, x, y+1))
        y++;
    return y;
}