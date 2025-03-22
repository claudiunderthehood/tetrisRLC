#include "game.h"
#include "replay.h"
#include <stdio.h>

int generate_actions(Piece piece, Action actions[], int max_actions){
    int count = 0;
    int saved_board[HEIGHT][WIDTH];
    copy_board(saved_board, board);
    int r, x;
    for(r = 0; r < piece.rotations; r++){
        for(x = -3; x < WIDTH; x++){
            copy_board(board, saved_board);
            int y = drop_piece(board, piece.shapes[r], x, 0);
            if (!check_collision(board, piece.shapes[r], x, y)) {
                place_piece_on_board(board, piece.shapes[r], x, y);
                int lines = clear_lines(board);
                actions[count].rotation = r;
                actions[count].x = x;
                actions[count].y = y;
                actions[count].lines_cleared = lines;
                copy_board(actions[count].resulting_board, board);
                double f[INPUT_SIZE];
                compute_features(board, f);
                double hidden1[HIDDEN_SIZE1], hidden2[HIDDEN_SIZE2];
                double reward = lines;
                double Q = nn_predict(f, hidden1, hidden2);
                actions[count].value = reward + _gamma * Q;
                count++;
                if(count >= max_actions){
                    copy_board(board, saved_board);
                    return count;
                }
            }
        }
    }
    copy_board(board, saved_board);
    return count;
}

void animate_fall(Piece piece, int rotation, int x, int final_y, int saved_board[HEIGHT][WIDTH]){
    int y;
    for(y = 0; y <= final_y; y++){
        int temp_board[HEIGHT][WIDTH];
        copy_board(temp_board, saved_board);
        int i, j;
        for (i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                if(piece.shapes[rotation][i][j]){
                    int bx = x + j;
                    int by = y + i;
                    if(bx >= 0 && bx < WIDTH && by >= 0 && by < HEIGHT)
                        temp_board[by][bx] = 2; // 2 indicates falling piece.
                }
            }
        }
        printf("\033[H\033[J");
        print_board_custom(temp_board);
        sleep_ms(10);
    }
}

int run_episode(void){
    int game_over = 0;
    int score = 0;
    int i, j;
    // Initialize board to empty.
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++)
            board[i][j] = 0;
    }
    
    while(!game_over){
        int saved_board[HEIGHT][WIDTH];
        copy_board(saved_board, board);
        
        int piece_index = rand() % NUM_PIECES;
        Piece current_piece = pieces[piece_index];
        
        Action actions[100];
        int num_actions = generate_actions(current_piece, actions, 100);
        if(num_actions == 0)
            break;
        
        int chosen_index = 0;
        if(((double)rand() / RAND_MAX) < epsilon)
            chosen_index = rand() % num_actions;
        else{
            double best = -1e9;
            for(i = 0; i < num_actions; i++){
                if (actions[i].value > best){
                    best = actions[i].value;
                    chosen_index = i;
                }
            }
        }
        
        double f_current[INPUT_SIZE];
        compute_features(saved_board, f_current);
        double hidden1[HIDDEN_SIZE1], hidden2[HIDDEN_SIZE2];
        double Q_current = nn_predict(f_current, hidden1, hidden2);
        
        animate_fall(current_piece, actions[chosen_index].rotation,
                     actions[chosen_index].x, actions[chosen_index].y, saved_board);
        
        copy_board(board, saved_board);
        place_piece_on_board(board, current_piece.shapes[actions[chosen_index].rotation],
                             actions[chosen_index].x, actions[chosen_index].y);
        int lines = clear_lines(board);
        score += lines;
        
        double f_next[INPUT_SIZE];
        compute_features(board, f_next);
        double Q_next = nn_predict(f_next, hidden1, hidden2);
        double reward = lines;
        
        double td_error = reward + _gamma * Q_next - Q_current;
        nn_update(f_current, td_error);
        
        Experience exp;
        for(i = 0; i < INPUT_SIZE; i++){
            exp.state[i] = f_current[i];
            exp.next_state[i] = f_next[i];
        }
        exp.reward = reward;
        exp.done = 0;
        for(j = 0; j < WIDTH; j++){
            if(board[0][j] == 1){
                exp.done = 1;
                game_over = 1;
                break;
            }
        }
        add_experience(exp);
        
        printf("\033[H\033[J");
        print_board_custom(board);
        sleep_ms(10);
  
        for(j = 0; j < WIDTH; j++){
            if(board[0][j] == 1){
                game_over = 1;
                break;
            }
        }
    }
    return score;
}