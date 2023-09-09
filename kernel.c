#include "io.h"

void main(){
    uart_init();
    uart_writeText("Hello, world! This is the Kernel Club\n");
    while(1){
        // do nothing
    }
}