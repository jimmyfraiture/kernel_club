#include "io.h"
#include "fb.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

struct __attribute__((aligned(16))) Point
{
    int x;
    int y;
    int dx;
    int dy;
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

void main()
{
    uart_init();
    fb_init();

    Point p1 = {0, 0, 0, 0};
    Point p2 = {0, 0, 0, 0};

    int x = 0;
    int y = 0;
    int px = 0;
    int py = 0;
    int vx = 1;
    int vy = 1;

    while (1) {
        if (x < 0 || x > SCREEN_WIDTH) {
            vx = -1 * vx;
        }

        if (y < 0 || y > SCREEN_HEIGHT) {
            vy = -1 * vy;
        }

        px = x;
        py = y;
        x = x + vx;
        y = y + vy;

        // Clear.
        drawCircle(px, py, 30, 0x00, 1);

        // Draw objects.
        drawCircle(x, y, 30, 0x0e, 1);
    }
}
