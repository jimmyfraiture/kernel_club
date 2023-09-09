#include "io.h"
#include "fb.h"
#include "debug.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

struct __attribute__((aligned(16))) Point
{
    int x;
    int y;
    int dx;
    int dy;
    int r;
    unsigned char color;
};

typedef struct Point Point;

void updatePoint(Point* p) {
    if (p->x < 0 || p->x > SCREEN_WIDTH) {
        p->dx = -1 * p->dx;
    }

    if (p->y < 0 || p->y > SCREEN_HEIGHT) {
        p->dy = -1 * p->dy;
    }
}

void sleep()
{
    // Magic sleep.
    for (int i = 0; i < 10000;)
    {
        ++i;
        drawPixel(0, 0, 0x00);
    }
}

void debug_print(long l) {
    char buffer[20]; // Ensure the buffer is big enough for 64-bit int.
    int_to_string(l, 10, buffer);
    uart_writeText(buffer);
}

void main()
{
    uart_init();
    fb_init();

    Point points[3] = {
        {100, 100, 2, -2, 10, 0xee},
        {150, 200, 2, 3, 20, 0xdd},
        {75, 250, 2, 3, 30, 0xaa},
    };

    while (1) {
        // Clear.
        for (int i = 0; i < 2; ++i) {
            drawCircle(
                points[i].x - points[i].dy, 
                points[i].y - points[i].dy, 
                30, 
                0x00, 
                1
            );
        }

        // Simulate physics.
        for (int i = 0; i < 2; ++i) {
            updatePoint(&points[i]);

            // Debug.
            uart_writeText("Point:");
            debug_print(points[i].x);
            debug_print(points[i].y);
            debug_print(points[i].dx);
            debug_print(points[i].dy);
        }

        // Draw objects.
        for (int i = 0; i < 2; ++i) {
            drawCircle(points[i].x, points[i].y, points[i].r, points[i].color, 1);
        }

        // Wait a bit.
        sleep();
    }
}
