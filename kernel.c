#include "io.h"
#include "fb.h"

void main()
{
    uart_init();
    fb_init();

    drawRect(0, 0, 1920, 1080, 0x23, 1);
    drawCircle(960,540,50,0x13,1);

    int radius = 50;
    int parity = 1;

    while (1) {
        drawRect(0, 0, 1920, 1080, 0x23, 1);
        drawCircle(960,540,radius,0x13,1);
        radius += parity;
        if(radius == 100 || radius == 50)
            parity *= -1;
    }
}