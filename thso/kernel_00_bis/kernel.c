#include "io.h"

void main()
{
    uart_init();

    while (1) {
        uart_writeText("Hello world!\n");
    }
}
