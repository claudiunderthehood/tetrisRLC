#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define WIDTH 10
#define HEIGHT 20
#define NUM_PIECES 7
#define NUM_EPISODES 1000
#define CHECKPOINT_FILENAME "checkpoint.txt"

#ifdef _WIN32
#define sleep_ms(x) Sleep(x)
#else
#define sleep_ms(x) usleep((x)*1000)
#endif

#define INPUT_SIZE 3
#define HIDDEN_SIZE 5
