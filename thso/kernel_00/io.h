#ifndef IO_FILE_H
#define IO_FILE_H

#define PERIPHERAL_BASE 0xFE000000

void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);

void uart_init();
void uart_writeText(char *buffer);
void uart_loadOutputFifo();
unsigned char uart_readByte();
unsigned int uart_isReadByteReady();
void uart_writeByteBlocking(unsigned char ch);
void uart_update();


#endif
