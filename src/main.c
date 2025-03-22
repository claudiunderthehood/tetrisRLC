#include "config.h"
#include "pieces.h"
#include "checkpoint.h"
#include "game.h"
#include "nn.h"
#include "replay.h"
#include <stdio.h>

int main(){
    srand(0);
    init_pieces();
    init_replay_buffer();

    int current_episode = 0;
    if(!load_checkpoint(CHECKPOINT_FILENAME, &current_episode)){
        nn_initialize();
        current_episode = 0;
        printf("No checkpoint found. Initialized new network parameters.\n");
        fflush(stdout);
        sleep_ms(5000);
    }else{
        printf("Loaded checkpoint from %s at episode %d.\n", CHECKPOINT_FILENAME, current_episode);
        fflush(stdout);
        sleep_ms(5000);
    }
    
    int target_update_frequency = 10;
    int best_score = 0;
    
    int episode;
    for(episode = current_episode + 1; episode <= NUM_EPISODES; episode++){
        int score = run_episode();
        printf("Episode %d: Score = %d\n", episode, score);
        fflush(stdout);
        
        epsilon *= 0.995;

        if(epsilon < 0.05)
            epsilon = 0.05;

        alpha *= 0.999;

        if(alpha < 0.0001)
            alpha = 0.0001;

        if(score > best_score){
            best_score = score;
            save_checkpoint("best_checkpoint.txt", episode);
            printf("New best score: %d at episode %d. Saved best checkpoint.\n", score, episode);
            fflush(stdout);
        }else if(score < best_score * 0.8){
            int dummy;
            if(load_checkpoint("best_checkpoint.txt", &dummy)){
                printf("Performance degraded (score %d vs best %d). Loading best checkpoint for refinement...\n", score, best_score);
                fflush(stdout);
                epsilon *= 0.98;
                if(epsilon < 0.05)
                    epsilon = 0.05;
                alpha *= 0.99;
                if(alpha < 0.0001)
                    alpha = 0.0001;
                printf("Refinement complete. Continuing training...\n");
                fflush(stdout);
            }
        }

        Experience batch[BATCH_SIZE];
        if(sample_experiences(batch, BATCH_SIZE) > 0){
            for(int i = 0; i < BATCH_SIZE; i++){
                double hidden_online[HIDDEN_SIZE1], hidden_online2[HIDDEN_SIZE2];
                double hidden_target[HIDDEN_SIZE1], hidden_target2[HIDDEN_SIZE2];
                double Q_current = nn_predict(batch[i].state, hidden_online, hidden_online2);
                double Q_next_target = nn_predict_target(batch[i].next_state, hidden_target, hidden_target2);
                double td_error = batch[i].reward + (batch[i].done ? 0 : _gamma * Q_next_target) - Q_current;
                nn_update(batch[i].state, td_error);
            }
        }

        if(episode % target_update_frequency == 0){
            update_target_network();
            printf("Updated target network at episode %d\n", episode);
            fflush(stdout);
        }
        
        save_checkpoint(CHECKPOINT_FILENAME, episode);
        sleep_ms(1000);
    }

    printf("\nFinal Neural Network Parameters:\n");
    printf("W1 (hidden layer weights):\n");
    for(int i = 0; i < HIDDEN_SIZE1; i++){
        for(int j = 0; j < INPUT_SIZE; j++){
            printf("%f ", W1[i][j]);
        }
        printf(" | b1: %f\n", b1[i]);
    }
    printf("W2 (hidden layer weights):\n");
    for(int i = 0; i < HIDDEN_SIZE2; i++){
        for(int j = 0; j < HIDDEN_SIZE1; j++){
            printf("%f ", W2[i][j]);
        }
        printf(" | b2: %f\n", b2[i]);
    }
    printf("W3 (output layer weights):\n");
    for(int j = 0; j < HIDDEN_SIZE2; j++){
        printf("%f ", W3[0][j]);
    }
    printf(" | b3: %f\n", b3);
    fflush(stdout);
    
    return 0;
}