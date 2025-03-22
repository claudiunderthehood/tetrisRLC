#include "checkpoint.h"
#include "nn.h"
#include <stdio.h>

void save_checkpoint(const char* filename, int episode){
    FILE *f = fopen(filename, "w");
    if(!f){
        printf("Error opening checkpoint file for writing.\n");
        return;
    }
    int i, j;
    for(i = 0; i < HIDDEN_SIZE1; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            fprintf(f, "%lf ", W1[i][j]);
        }
        fprintf(f, "\n");
    }

    for(i = 0; i < HIDDEN_SIZE1; i++){
        fprintf(f, "%lf ", b1[i]);
    }
    fprintf(f, "\n");

    for(i = 0; i < HIDDEN_SIZE2; i++){
        for(j = 0; j < HIDDEN_SIZE1; j++){
            fprintf(f, "%lf ", W2[i][j]);
        }
        fprintf(f, "\n");
    }

    for(i = 0; i < HIDDEN_SIZE2; i++){
        fprintf(f, "%lf ", b2[i]);
    }
    fprintf(f, "\n");

    for(j = 0; j < HIDDEN_SIZE2; j++){
        fprintf(f, "%lf ", W3[0][j]);
    }
    fprintf(f, "\n");

    fprintf(f, "%lf\n", b3);

    fprintf(f, "%d\n", episode);
    fprintf(f, "%lf\n", epsilon);
    fprintf(f, "%lf\n", alpha);
    fprintf(f, "%lf\n", _gamma);
    fprintf(f, "%lf\n", lambda);
    
    fclose(f);
}

int load_checkpoint(const char* filename, int *episode){
    FILE *f = fopen(filename, "r");
    if(!f)
        return 0;
    int i, j;
    for(i = 0; i < HIDDEN_SIZE1; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            if(fscanf(f, "%lf", &W1[i][j]) != 1) { fclose(f); return 0; }
        }
    }
    for(i = 0; i < HIDDEN_SIZE1; i++){
        if(fscanf(f, "%lf", &b1[i]) != 1) { fclose(f); return 0; }
    }

    for(i = 0; i < HIDDEN_SIZE2; i++){
        for(j = 0; j < HIDDEN_SIZE1; j++){
            if(fscanf(f, "%lf", &W2[i][j]) != 1) { fclose(f); return 0; }
        }
    }
 
    for(i = 0; i < HIDDEN_SIZE2; i++){
        if(fscanf(f, "%lf", &b2[i]) != 1) { fclose(f); return 0; }
    }

    for(j = 0; j < HIDDEN_SIZE2; j++){
        if(fscanf(f, "%lf", &W3[0][j]) != 1) { fclose(f); return 0; }
    }

    if(fscanf(f, "%lf", &b3) != 1) { fclose(f); return 0; }
    
    if(fscanf(f, "%d", episode) != 1) { fclose(f); return 0; }
    if(fscanf(f, "%lf", &epsilon) != 1) { fclose(f); return 0; }
    if(fscanf(f, "%lf", &alpha) != 1) { fclose(f); return 0; }
    if(fscanf(f, "%lf", &_gamma) != 1) { fclose(f); return 0; }
    if(fscanf(f, "%lf", &lambda) != 1) { fclose(f); return 0; }
    
    fclose(f);
    return 1;
}