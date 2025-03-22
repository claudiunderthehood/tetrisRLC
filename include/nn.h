#pragma once

#include "config.h"

#define HIDDEN_SIZE1 20
#define HIDDEN_SIZE2 10

// Online network parameters
extern double W1[HIDDEN_SIZE1][INPUT_SIZE];
extern double b1[HIDDEN_SIZE1];
extern double W2[HIDDEN_SIZE2][HIDDEN_SIZE1];
extern double b2[HIDDEN_SIZE2];
extern double W3[1][HIDDEN_SIZE2];
extern double b3;

extern double alpha;    // learning rate
extern double _gamma;   // discount factor
extern double epsilon;  // exploration rate
extern double lambda;   // L2 regularization coefficient

// Target network parameters
extern double W1_target[HIDDEN_SIZE1][INPUT_SIZE];
extern double b1_target[HIDDEN_SIZE1];
extern double W2_target[HIDDEN_SIZE2][HIDDEN_SIZE1];
extern double b2_target[HIDDEN_SIZE2];
extern double W3_target[1][HIDDEN_SIZE2];
extern double b3_target;

// Function declarations
void nn_initialize(void);
double nn_predict(double features[INPUT_SIZE], double hidden1[HIDDEN_SIZE1], double hidden2[HIDDEN_SIZE2]);
double nn_predict_target(double features[INPUT_SIZE], double hidden1_out[HIDDEN_SIZE1], double hidden2_out[HIDDEN_SIZE2]);
void nn_update(double features[INPUT_SIZE], double td_error);
void compute_features(int b[HEIGHT][WIDTH], double features[INPUT_SIZE]);
void update_target_network(void);