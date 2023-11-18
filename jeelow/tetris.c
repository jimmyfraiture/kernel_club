#include "gpu.h"
#include "io.h"
#include "std.h"
#include "fb.h"

void drawShape(int x, int y, int shape[4][4], int color) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                setSquare(x + j, y + i, color);
            }
        }
    }
}
void main_tetris(){
    int I_shape[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int O_shape[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int T_shape[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int S_shape[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    int Z_shape[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int J_shape[4][4] = {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int L_shape[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };

    // all shape in an array
    int *shapes[7] = {I_shape, O_shape, T_shape, S_shape, Z_shape, J_shape, L_shape};

    // init the game
    clearScreen();
    int current_shape = 2;
    int current_x = 0;
    int current_y = 0;
    int current_color = 0x10;
    int current_rotation = 0;
    int i, j;
    int iteration = 0;
    int score = 0;
    int game_over = 0;
    clearScreen();

    // draw the ground

    // main loop
    while (1) {
        //if current_y is 35, then the shape is on the ground and we spawn another shape
        if(current_y == 35){
            current_shape = (current_shape + 1) % 7;
            current_x = 0;
            current_y = 0;
            current_color = current_color + 0x10;
        }

        // draw the current shape
        drawShape(current_x, current_y, shapes[current_shape], 0xf0);
        current_y++;
        drawShape(current_x, current_y, shapes[current_shape], current_color);

        wait_nsec(300000);

        // // check if the shape is on the ground
        // int on_the_ground = 0;
        // for (i = 0; i < 4; i++) {
        //     if (current_y + i >= 35) {
        //         on_the_ground = 1;
        //         break;
        //     }
        // }

        // // check if the shape is on another shape
        // int on_another_shape = 0;
        // for (i = 0; i < 4; i++) {
        //     if (on_the_ground == 1) break;
        //     for (j = 0; j < 4; j++) {
        //         if (old_shapes[current_shape][i][j] == 1) {
        //             if (getSquare(current_x + j, current_y + i + 1) != 0) {
        //                 on_another_shape = 1;
        //                 break;
        //             }
        //         }
        //     }
        // }

        // // if the shape is on the ground or on another shape
        // if (on_the_ground == 1 || on_another_shape == 1) {
        //     // draw the shape with the color of the ground
        //     drawShape(current_x, current_y, shapes[current_shape], 0x30);

        //     // check if the game is over
        //     if (current_y == 0) {
        //         game_over = 1;
        //         break;
        //     }

        //     // check if there is a line to delete
        //     int line_to_delete = 1;
        //     for (i = 0; i < 40; i++) {
        //         if (getSquare(i, current_y) == 0) {
        //             line_to_delete = 0;
        //             break;
        //         }
        //     }

        //     // delete the line
        //     if (line_to_delete == 1) {
        //         for (i = current_y; i > 0; i--) {
        //             for (j = 0; j < 40; j++) {
        //                 setSquare(j, i, getSquare(j, i - 1));
        //             }
        //         }
        //         score += 100;
        //     }

        //     // get a new shape
        //     current_shape = rand() % 7;
        //     current_x = 0;
        //     current_y = 0;
        //     current_color = 0x23;
        //     current_rotation = 0;
        // } else {
        //     // draw the shape with the color of the ground
        //     drawShape(current_x, current_y, shapes[current_shape], 0x30);

        //     // move the shape
        //     current_y++;
        // }
    }

}