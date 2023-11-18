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

void add_random_bonus(){
    random_index_x = (random_index_x + 1) % 30;
    random_index_y = (random_index_y + 1) % 30;

    int x = random_seed_x[random_index_x];
    int y = random_seed_y[random_index_y];
    setSquare(x, y, 0x13);
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
        if (uart_isReadByteReady()) {
            char c = uart_readByte();
            if (c == 'w') {
                x_direction = 0;
                y_direction = -1;
            } else if (c == 'a') {
                x_direction = -1;
                y_direction = 0;
            } else if (c == 's') {
                x_direction = 0;
                y_direction = 1;
            } else if (c == 'd') {
                x_direction = 1;
                y_direction = 0;
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

        // Move tail
        node *current = head;
        while (current->next->next != NULL)
            current = current->next;
        setSquare(current->next->x, current->next->y, 0x30);
        free(current->next);
        current->next = NULL;

        // Loopers
        iteration = (iteration + 1) % 100;
        wait_nsec(500000);
    
    }
}