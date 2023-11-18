#include "fb.h"
#include "gpu.h"

void set_square(int x, int y, unsigned char attr){
    int cell_height = (SCREEN_HEIGHT - 2 * RAW_MARGINS) / MATRIX_HEIGHT;
    int cell_width = cell_height;
    int x0 = RAW_MARGINS + x * cell_width;
    int y0 = RAW_MARGINS + y * cell_height;
    int x1 = x0 + cell_width;
    int y1 = y0 + cell_height;
    drawRect(x0, y0, x1, y1, attr, 1);
}

void clear_screen(){
    drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00, 1);
    drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x30, 1);
    drawRect(
            RAW_MARGINS - NET_MARGINS,
            RAW_MARGINS - NET_MARGINS,
            SCREEN_WIDTH - RAW_MARGINS + NET_MARGINS,
            SCREEN_HEIGHT - RAW_MARGINS + NET_MARGINS,
            0x00,
            1
    );
}

void game_over_screen(){
    int go_x[71] = {0, 2, 5, 6, 9, 12, 17, 22, 23, 27, 28, 29, 31, 32, 33, 34, 0, 2, 4, 7, 9, 12, 17, 21, 24, 26, 31, 0, 1, 2, 4, 7, 9, 12, 17, 21, 24, 27, 28, 31, 32, 33, 1, 4, 7, 9, 12, 17, 21, 24, 29, 31, 1, 5, 6, 9, 10, 11, 12, 17, 18, 19, 22, 23, 26, 27, 28, 31, 32, 33, 34};
    int go_y[71] = {0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 3, 3, 3, 3,  3,  3,  3,  3,  3,  3, 4, 4, 4, 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4};
    int x_shift = 8; // todo compute them instead please
    int y_shift = 16;
    drawRect(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT, 0x00, 1);
    for(int i = 0; i < 71; i++){
        set_square(go_x[i] + x_shift, go_y[i] + y_shift, 0x44);
    }
}