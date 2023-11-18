#include "gpu.h"
#include "io.h"
#include "std.h"
#include "fb.h"
typedef struct node {
    int x;
    int y;
    struct node *next;
} node;

void game_over(){
    game_over_screen();
    while(1){}
}

void main_snake(){
    // Snake
    int x_direction = 1;
    int y_direction = 0;
    node *head = malloc(sizeof(node));
    node *n1 = malloc(sizeof(node));
    node *n2 = malloc(sizeof(node));

    if(head == NULL || n1 == NULL || n2 == NULL) {
        set_square(0, 0, 0x55);
        while(1);
    }

    head->x = 5; head->y = 5;
    n1->x = 5; n1->y = 6;
    n2->x = 6; n2->y = 6;
    head->next = n1;
    n1->next = n2;
    n2->next = NULL;

    // Bonus
    int x_bonus = 20; //rand() % MATRIX_WIDTH;
    int y_bonus = 20; //rand() % MATRIX_HEIGHT;

    // Display
    clear_screen();
    set_square(head->x, head->y, 0x23);
    set_square(n1->x, n1->y, 0x23);
    set_square(n2->x, n2->y, 0x23);
    set_square(x_bonus, y_bonus, 0x43);

    while (1) {
        // Compute the direction of the snake
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

        // Compute new head position
        int new_x = head->x + x_direction;
        int new_y = head->y + y_direction;

        if (new_x < 0) new_x = MATRIX_WIDTH - 1;
        if (new_x >= MATRIX_WIDTH) new_x = 0;
        if (new_y < 0) new_y = MATRIX_HEIGHT - 1;
        if (new_y >= MATRIX_HEIGHT) new_y = 0;

        // Build new head
        node *new_head = malloc(sizeof(node));
        if(new_head == NULL){
            drawString(500, 200, "Error on the malloc. FUCK ! ", 0x0f);
        }
        new_head->x = new_x;
        new_head->y = new_y;
        new_head->next = head;
        head = new_head;
        set_square(head->x, head->y, 0x23);

        // Check if the new head is on a bonus
        if(head->x == x_bonus && head->y == y_bonus){
            // Add a new bonus somewhere
            x_bonus = rand() % MATRIX_WIDTH;
            y_bonus = rand() % MATRIX_HEIGHT;
            set_square(x_bonus, y_bonus, 0x43);
        } else { // If not, move the tail
            node *current = head;
            while (current->next->next != NULL) {
                current = current->next;
                if(current->x == head->x && current->y == head->y){
                    game_over();
                }
            }
            set_square(current->next->x, current->next->y, 0x00); // todo ensure this is ok
            free(current->next);
            current->next = NULL;
        }

        wait_nsec(300000);    
    }
}