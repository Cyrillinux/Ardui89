/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */

#ifndef _89_UART_STDIO_
#define _89_UART_STDIO_

#ifndef F_CPU
#define F_CPU 11059200
#endif
#include <stdarg.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

typedef struct _89_uart {
    char (*available)(void);
    void (*begin)(int);
    void (*printf)(const char *, ...);
    void (*printfln)(const char *, ...);
    void (*print)(const char *, ...);
    void (*println)(const char *, ...);
    char (*read)(void);
    void (*readString)(char *buffer);
};

extern struct _89_uart Serial;

// Prototypes
void Serial89Init(void);
void _89_uart_init(unsigned long baudrate, unsigned long fosc);
void _89_uart_send_char(char c);
void _89_int_to_string(int num, char *str);
void _89_uart_printf(const char *format, ...);
void _89_uart_printfln(const char *format, ...);
void _89_uart_begin(int baudrate);
char _89_uart_available(void);
char _89_uart_read_char(void);
void _89_uart_read_string(char *_89_uart_buffer);

#endif
