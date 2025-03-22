#include "replay.h"
#include <stdlib.h>

static Experience replay_buffer[REPLAY_BUFFER_SIZE];
static int replay_count = 0;
static int replay_index = 0;

void init_replay_buffer(void){
    replay_count = 0;
    replay_index = 0;
}

void add_experience(Experience exp){
    replay_buffer[replay_index] = exp;
    replay_index = (replay_index + 1) % REPLAY_BUFFER_SIZE;
    if(replay_count < REPLAY_BUFFER_SIZE)
        replay_count++;
}

int sample_experiences(Experience batch[], int batch_size){
    if (replay_count < batch_size)
        return 0;
    for(int i = 0; i < batch_size; i++){
        int index = rand() % replay_count;
        batch[i] = replay_buffer[index];
    }
    return batch_size;
}