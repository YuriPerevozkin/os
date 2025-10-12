#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stddef.h>

void putchar_at(unsigned char ch, uint8_t color, size_t y, size_t x);
void putchar(unsigned char ch, uint8_t color);
void kprint(char* msg, uint8_t color);
void init_tty();

#endif
