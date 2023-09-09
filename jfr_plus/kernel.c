#include "io.h"
#include "fb.h"
#include "gpu.h"
#include "snake.h"
#include "std.h"

void main() {
    uart_init();
    fb_init();
    initialize_heap();

    main_snake();
}