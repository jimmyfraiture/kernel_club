#include "gpu.h"
#include "io.h"
#include "std.h"
typedef struct node {
    int x;
    int y;
    struct node *next;
} node;

void main_snake(){
    int x_direction = 1;
    int y_direction = 0;

    node *head = malloc(sizeof(node));
    node *n1 = malloc(sizeof(node));
    node *n2 = malloc(sizeof(node));
    head->x = 5; head->y = 5;
    n1->x = 5; n1->y = 6;
    n2->x = 5; n2->y = 7;
    head->next = n1;
    n1->next = n2;
    n2->next = NULL;

    // Init and malloc an array of 25 int
    clearScreen();
    setSquare(head->x, head->y, 0x13);
    setSquare(n1->x, n1->y, 0x13);
    setSquare(n2->x, n2->y, 0x13);
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

        int new_x = head->x + x_direction;
        int new_y = head->y + y_direction;
        node *new_head = malloc(sizeof(node));
        new_head->x = new_x;
        new_head->y = new_y;
        new_head->next = head;
        head = new_head;
        setSquare(head->x, head->y, 0x13);

        node *current = head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        setSquare(current->next->x, current->next->y, 0x00);
        free(current->next);
        current->next = NULL;
    }
}