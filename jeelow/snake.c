#include "gpu.h"
#include "io.h"
#include "std.h"
#include "fb.h"
typedef struct node {
    int x;
    int y;
    struct node *next;
} node;

// Random list of integers
int random_seed_x[30] = {16, 18, 14, 20, 9, 30, 11, 14, 20, 22, 16, 16, 12, 10, 24, 28, 16, 20, 4, 8, 3, 16, 19, 22, 20, 9, 17, 5, 23, 21};
int random_seed_y[30] = {13, 23, 2, 10, 15, 9, 26, 8, 20, 25, 17, 16, 24, 1, 19, 7, 3, 11, 6, 29, 12, 28, 27, 5, 21, 14, 22, 4, 30, 10};
int random_index_x = 0;
int random_index_y = 0;
int bonus_available = 0;

void add_random_bonus(){
    random_index_x = (random_index_x + 1) % 30;
    random_index_y = (random_index_y + 1) % 30;

    int x = random_seed_x[random_index_x];
    int y = random_seed_y[random_index_y];
    setSquare(x, y, 0x13);
    bonus_available = 1;
}

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

void main_snake(){
    int x_direction = 1;
    int y_direction = 0;
    int iteration = 0;

    // Snake
    node *head = malloc(sizeof(node));
    node *n1 = malloc(sizeof(node));
    node *n2 = malloc(sizeof(node));

    if(head == NULL || n1 == NULL || n2 == NULL) {
        setSquare(0, 0, 0x55);
        while(1);
    }

    head->x = 5; head->y = 5;
    n1->x = 5; n1->y = 6;
    n2->x = 6; n2->y = 6;
    head->next = n1;
    n1->next = n2;
    n2->next = NULL;

    // Init and malloc an array of 25 int
    clearScreen();
    setSquare(head->x, head->y, 0x23);
    setSquare(n1->x, n1->y, 0x23);
    setSquare(n2->x, n2->y, 0x23);

    while (1) {
        // Compute the direction of the snake
        if(bonus_available == 1){
            int x_bonus = random_seed_x[random_index_x];
            int y_bonus = random_seed_y[random_index_y];
            if(x_bonus > head->x){
                x_direction = 1;
                y_direction = 0;
            } else if(x_bonus < head-> x){
                x_direction = -1;
                y_direction = 0;
            } else if(y_bonus < head-> y){
                y_direction = -1;
                x_direction = 0;
            } else{
                y_direction = 1;
                x_direction = 0;
            }
        }

        if (iteration == 0) {
            add_random_bonus();
        }
        int new_x = head->x + x_direction;
        int new_y = head->y + y_direction;

        if (new_x < 0) new_x = 40 - 1;
        if (new_x >= 40) new_x = 0;
        if (new_y < 0) new_y = 35 - 1;
        if (new_y >= 35) new_y = 0;

        // Get new head
        node *new_head = malloc(sizeof(node)); // todo the malloc does not work
        if(new_head == NULL){
            drawString(500, 200, "Error on the malloc. FUCK ! ", 0x0f);
        }
        new_head->x = new_x;
        new_head->y = new_y;
        new_head->next = head;
        head = new_head;
        setSquare(head->x, head->y, 0x23);

        // Check if the new head is on a bonus
        if(head->x == random_seed_x[random_index_x] && head->y == random_seed_x[random_index_y]){
            bonus_available = 0;
        } else { // If not, move the tail
            node *current = head;
            while (current->next->next != NULL)
                current = current->next;
            setSquare(current->next->x, current->next->y, 0x30);
            free(current->next);
            current->next = NULL;
        }

        // Loopers
        iteration = (iteration + 1) % 60;
        wait_nsec(300000);
    
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
    int current_color = 0x23;
    int current_rotation = 0;
    int i, j;
    int iteration = 0;
    int score = 0;
    int game_over = 0;

    // main loop
    while (1) {
        // draw the current shape
        drawShape(current_x, current_y, shapes[current_shape], current_color);
        current_y++;
        //if current_y is 35, then the shape is on the ground and we spawn another shape
        if(current_y == 35){
            current_shape = rand() % 7;
            current_x = 0;
            current_y = 0;
            current_color = 0x40;
        }

        wait_nsec(300000);
        clearScreen();

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