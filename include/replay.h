#pragma once

#include "config.h"

#define REPLAY_BUFFER_SIZE 1000
#define BATCH_SIZE 32

typedef struct {
    double state[INPUT_SIZE];
    double reward;
    double next_state[INPUT_SIZE];
    int done;
} Experience;

void init_replay_buffer(void);
void add_experience(Experience exp);
int sample_experiences(Experience batch[], int batch_size);