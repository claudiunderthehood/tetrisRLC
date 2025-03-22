#include "pieces.h"

Piece pieces[NUM_PIECES];

void init_pieces(void){
    int i, j;
    // I piece (index 0): 2 rotations
    pieces[0].rotations = 2;
    pieces[0].size = 4;
    int I0[4][4] = {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    };
    int I1[4][4] = {
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
    };
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            pieces[0].shapes[0][i][j] = I0[i][j];
            pieces[0].shapes[1][i][j] = I1[i][j];
        }
    }
    // O piece (index 1): 1 rotation
    pieces[1].rotations = 1;
    pieces[1].size = 2;
    int O0[2][2] = {
        {1,1},
        {1,1}
    };
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            pieces[1].shapes[0][i][j] = 0;
        }
    }
    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            pieces[1].shapes[0][i][j] = O0[i][j];
        }
    }
    // T piece (index 2): 4 rotations
    pieces[2].rotations = 4;
    pieces[2].size = 3;
    int T0[3][3] = {
        {0,1,0},
        {1,1,1},
        {0,0,0}
    };
    int T1[3][3] = {
        {0,1,0},
        {0,1,1},
        {0,1,0}
    };
    int T2[3][3] = {
        {0,0,0},
        {1,1,1},
        {0,1,0}
    };
    int T3[3][3] = {
        {0,1,0},
        {1,1,0},
        {0,1,0}
    };
    for(int r = 0; r < 4; r++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                pieces[2].shapes[r][i][j] = 0;
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            pieces[2].shapes[0][i][j] = T0[i][j];
            pieces[2].shapes[1][i][j] = T1[i][j];
            pieces[2].shapes[2][i][j] = T2[i][j];
            pieces[2].shapes[3][i][j] = T3[i][j];
        }
    }
    // S piece (index 3): 2 rotations
    pieces[3].rotations = 2;
    pieces[3].size = 3;
    int S0[3][3] = {
        {0,1,1},
        {1,1,0},
        {0,0,0}
    };
    int S1[3][3] = {
        {1,0,0},
        {1,1,0},
        {0,1,0}
    };
    for(int r = 0; r < 2; r++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                pieces[3].shapes[r][i][j] = 0;
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            pieces[3].shapes[0][i][j] = S0[i][j];
            pieces[3].shapes[1][i][j] = S1[i][j];
        }
    }
    // Z piece (index 4): 2 rotations
    pieces[4].rotations = 2;
    pieces[4].size = 3;
    int Z0[3][3] = {
        {1,1,0},
        {0,1,1},
        {0,0,0}
    };
    int Z1[3][3] = {
        {0,1,0},
        {1,1,0},
        {1,0,0}
    };
    for(int r = 0; r < 2; r++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                pieces[4].shapes[r][i][j] = 0;
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            pieces[4].shapes[0][i][j] = Z0[i][j];
            pieces[4].shapes[1][i][j] = Z1[i][j];
        }
    }
    // J piece (index 5): 4 rotations
    pieces[5].rotations = 4;
    pieces[5].size = 3;
    int J0[3][3] = {
        {1,0,0},
        {1,1,1},
        {0,0,0}
    };
    int J1[3][3] = {
        {0,1,1},
        {0,1,0},
        {0,1,0}
    };
    int J2[3][3] = {
        {0,0,0},
        {1,1,1},
        {0,0,1}
    };
    int J3[3][3] = {
        {0,1,0},
        {0,1,0},
        {1,1,0}
    };
    for(int r = 0; r < 4; r++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                pieces[5].shapes[r][i][j] = 0;
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            pieces[5].shapes[0][i][j] = J0[i][j];
            pieces[5].shapes[1][i][j] = J1[i][j];
            pieces[5].shapes[2][i][j] = J2[i][j];
            pieces[5].shapes[3][i][j] = J3[i][j];
        }
    }
    // L piece (index 6): 4 rotations
    pieces[6].rotations = 4;
    pieces[6].size = 3;
    int L0[3][3] = {
        {0,0,1},
        {1,1,1},
        {0,0,0}
    };
    int L1[3][3] = {
        {0,1,0},
        {0,1,0},
        {0,1,1}
    };
    int L2[3][3] = {
        {0,0,0},
        {1,1,1},
        {1,0,0}
    };
    int L3[3][3] = {
        {1,1,0},
        {0,1,0},
        {0,1,0}
    };
    for(int r = 0; r < 4; r++){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                pieces[6].shapes[r][i][j] = 0;
            }
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            pieces[6].shapes[0][i][j] = L0[i][j];
            pieces[6].shapes[1][i][j] = L1[i][j];
            pieces[6].shapes[2][i][j] = L2[i][j];
            pieces[6].shapes[3][i][j] = L3[i][j];
        }
    }
}
