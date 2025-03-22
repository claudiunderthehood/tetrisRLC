#include "nn.h"
#include <math.h>
#include <string.h>

double W1[HIDDEN_SIZE1][INPUT_SIZE];
double b1[HIDDEN_SIZE1];
double W2[HIDDEN_SIZE2][HIDDEN_SIZE1];
double b2[HIDDEN_SIZE2];
double W3[1][HIDDEN_SIZE2];
double b3;

double alpha = 0.05;
double _gamma = 0.9;
double epsilon = 0.1;
double lambda = 0.0001;

double W1_target[HIDDEN_SIZE1][INPUT_SIZE];
double b1_target[HIDDEN_SIZE1];
double W2_target[HIDDEN_SIZE2][HIDDEN_SIZE1];
double b2_target[HIDDEN_SIZE2];
double W3_target[1][HIDDEN_SIZE2];
double b3_target;

static double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

void nn_initialize(void){
    int i, j;
    // Initialize layer 1
    for(i = 0; i < HIDDEN_SIZE1; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            W1[i][j] = ((double)rand() / RAND_MAX * 0.1) - 0.05;
        }
        b1[i] = ((double)rand() / RAND_MAX * 0.1) - 0.05;
    }
    // Initialize layer 2
    for(i = 0; i < HIDDEN_SIZE2; i++){
        for(j = 0; j < HIDDEN_SIZE1; j++){
            W2[i][j] = ((double)rand() / RAND_MAX * 0.1) - 0.05;
        }
        b2[i] = ((double)rand() / RAND_MAX * 0.1) - 0.05;
    }
    // Initialize output layer
    for(j = 0; j < HIDDEN_SIZE2; j++){
        W3[0][j] = ((double)rand() / RAND_MAX * 0.1) - 0.05;
    }
    b3 = ((double)rand() / RAND_MAX * 0.1) - 0.05;
    
    // Initialize target network
    update_target_network();
}

double nn_predict(double features[INPUT_SIZE], double hidden1[HIDDEN_SIZE1], double hidden2[HIDDEN_SIZE2]){
    int i, j;
    // Layer 1
    for(i = 0; i < HIDDEN_SIZE1; i++){
        double sum = 0.0;
        for(j = 0; j < INPUT_SIZE; j++){
            sum += W1[i][j] * features[j];
        }
        sum += b1[i];
        hidden1[i] = sigmoid(sum);
    }
    // Layer 2
    for(i = 0; i < HIDDEN_SIZE2; i++){
        double sum = 0.0;
        for(j = 0; j < HIDDEN_SIZE1; j++){
            sum += W2[i][j] * hidden1[j];
        }
        sum += b2[i];
        hidden2[i] = sigmoid(sum);
    }
    double output = 0.0;
    for(j = 0; j < HIDDEN_SIZE2; j++){
        output += W3[0][j] * hidden2[j];
    }
    output += b3;
    return output;
}

double nn_predict_target(double features[INPUT_SIZE], double hidden1_out[HIDDEN_SIZE1], double hidden2_out[HIDDEN_SIZE2]){
    int i, j;
    double temp_hidden1[HIDDEN_SIZE1];
    double temp_hidden2[HIDDEN_SIZE2];
    // Layer 1
    for(i = 0; i < HIDDEN_SIZE1; i++){
        double sum = 0.0;
        for(j = 0; j < INPUT_SIZE; j++){
            sum += W1_target[i][j] * features[j];
        }
        sum += b1_target[i];
        temp_hidden1[i] = sigmoid(sum);
    }
    // Layer 2
    for(i = 0; i < HIDDEN_SIZE2; i++){
        double sum = 0.0;
        for(j = 0; j < HIDDEN_SIZE1; j++){
            sum += W2_target[i][j] * temp_hidden1[j];
        }
        sum += b2_target[i];
        temp_hidden2[i] = sigmoid(sum);
    }
    // Copy outputs
    memcpy(hidden1_out, temp_hidden1, sizeof(temp_hidden1));
    memcpy(hidden2_out, temp_hidden2, sizeof(temp_hidden2));
    
    double output = 0.0;
    for(j = 0; j < HIDDEN_SIZE2; j++){
        output += W3_target[0][j] * temp_hidden2[j];
    }
    output += b3_target;
    return output;
}

void nn_update(double features[INPUT_SIZE], double td_error){
    int i, j;
    double hidden1[HIDDEN_SIZE1], hidden2[HIDDEN_SIZE2];

    for(i = 0; i < HIDDEN_SIZE1; i++){
        double sum = 0.0;
        for(j = 0; j < INPUT_SIZE; j++){
            sum += W1[i][j] * features[j];
        }
        sum += b1[i];
        hidden1[i] = sigmoid(sum);
    }

    for(i = 0; i < HIDDEN_SIZE2; i++){
        double sum = 0.0;
        for(j = 0; j < HIDDEN_SIZE1; j++){
            sum += W2[i][j] * hidden1[j];
        }
        sum += b2[i];
        hidden2[i] = sigmoid(sum);
    }
    double output = 0.0;
    for(j = 0; j < HIDDEN_SIZE2; j++){
        output += W3[0][j] * hidden2[j];
    }
    output += b3;
    
    double delta3 = td_error;
    
    double delta2[HIDDEN_SIZE2];
    for(i = 0; i < HIDDEN_SIZE2; i++){
        double deriv = hidden2[i] * (1 - hidden2[i]);
        delta2[i] = delta3 * W3[0][i] * deriv;
    }

    double delta1[HIDDEN_SIZE1];
    for(i = 0; i < HIDDEN_SIZE1; i++){
        double sum = 0.0;
        for(j = 0; j < HIDDEN_SIZE2; j++){
            sum += delta2[j] * W2[j][i];
        }
        double deriv = hidden1[i] * (1 - hidden1[i]);
        delta1[i] = sum * deriv;
    }

    for(j = 0; j < HIDDEN_SIZE2; j++){
        double grad_W3 = delta3 * hidden2[j];
        W3[0][j] += alpha * (grad_W3 - lambda * W3[0][j]);
    }
    b3 += alpha * (delta3 - lambda * b3);
    
    for(i = 0; i < HIDDEN_SIZE2; i++){
        for(j = 0; j < HIDDEN_SIZE1; j++){
            double grad_W2 = delta2[i] * hidden1[j];
            W2[i][j] += alpha * (grad_W2 - lambda * W2[i][j]);
        }
        b2[i] += alpha * (delta2[i] - lambda * b2[i]);
    }

    for(i = 0; i < HIDDEN_SIZE1; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            double grad_W1 = delta1[i] * features[j];
            W1[i][j] += alpha * (grad_W1 - lambda * W1[i][j]);
        }
        b1[i] += alpha * (delta1[i] - lambda * b1[i]);
    }
}

void compute_features(int b[HEIGHT][WIDTH], double features[INPUT_SIZE]){
    int col_heights[WIDTH] = {0};
    int i, j;
    for(j = 0; j < WIDTH; j++){
        int col_height = 0;
        for(i = 0; i < HEIGHT; i++){
            if(b[i][j] == 1){
                col_height = HEIGHT - i;
                break;
            }
        }
        col_heights[j] = col_height;
    }
    int agg_height = 0;
    for(j = 0; j < WIDTH; j++){
        agg_height += col_heights[j];
    }
    int holes = 0;
    for(j = 0; j < WIDTH; j++){
        int block_found = 0;
        for(i = 0; i < HEIGHT; i++){
            if(b[i][j] == 1)
                block_found = 1;
            else if(block_found)
                holes++;
        }
    }
    int bumpiness = 0;
    for(j = 0; j < WIDTH - 1; j++){
        bumpiness += abs(col_heights[j] - col_heights[j+1]);
    }
    features[0] = (double)agg_height;
    features[1] = (double)holes;
    features[2] = (double)bumpiness;
}

void update_target_network(void){
    int i, j;
    for(i = 0; i < HIDDEN_SIZE1; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            W1_target[i][j] = W1[i][j];
        }
        b1_target[i] = b1[i];
    }
    for(i = 0; i < HIDDEN_SIZE2; i++){
        for(j = 0; j < HIDDEN_SIZE1; j++){
            W2_target[i][j] = W2[i][j];
        }
        b2_target[i] = b2[i];
    }
    for(j = 0; j < HIDDEN_SIZE2; j++){
        W3_target[0][j] = W3[0][j];
    }
    b3_target = b3;
}