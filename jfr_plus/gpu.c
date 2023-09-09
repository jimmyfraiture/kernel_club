#include "fb.h"

unsigned int screen_width = 1920;
unsigned int screen_height = 1080;
unsigned int matrix_width = 40;
unsigned int matrix_height = 30;

unsigned int margins = 50;


void setSquare(int x, int y, unsigned char attr){
    int cell_width = (screen_width - 2 * margins) / matrix_width;
    int cell_height = (screen_height - 2 * margins) / matrix_height;

    int x0 = margins + x * cell_width;
    int y0 = margins + y * cell_height;
    int x1 = x0 + cell_width;
    int y1 = y0 + cell_height;
    drawRect(x0, y0, x1, y1, attr, 1);
}

void clearScreen(){
    drawRect(0, 0, screen_width , screen_height, 0x00, 1);
}