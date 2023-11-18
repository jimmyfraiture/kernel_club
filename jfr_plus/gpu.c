#include "fb.h"
#include "gpu.h"

void setSquare(int x, int y, unsigned char attr){
    int cell_height = (SCREEN_HEIGHT - 2 * RAW_MARGINS) / MATRIX_HEIGHT;
    int cell_width = cell_height;

    int x0 = RAW_MARGINS + x * cell_width;
    int y0 = RAW_MARGINS + y * cell_height;
    int x1 = x0 + cell_width;
    int y1 = y0 + cell_height;
    drawRect(x0, y0, x1, y1, attr, 1);
}

void clearScreen(){
    drawRect(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT, 0x00, 1);
    drawRect(0, 0, SCREEN_WIDTH , SCREEN_HEIGHT, 0x30, 1);
    drawRect(
            RAW_MARGINS - NET_MARGINS,
            RAW_MARGINS - NET_MARGINS,
            SCREEN_WIDTH - RAW_MARGINS + NET_MARGINS,
            SCREEN_HEIGHT - RAW_MARGINS + NET_MARGINS,
            0x00,
            1
    );
}
