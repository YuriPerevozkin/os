#include <stdint.h>
#include <stddef.h>
#include "screen.h"

size_t current_row;
size_t current_col;
uint16_t* buffer;

static inline uint16_t vga_entry(char ch, uint8_t color) {
    return (uint16_t) ch | color << 8;
}

static inline size_t buffer_index(size_t y, size_t x) {
    return y * VGA_WIDTH + x;
}

static void newline() {
    if (current_row != VGA_HEIGHT-1) {
        current_row++;
        current_col = 0;
    }
}

static void putchar_at(char ch, uint8_t color, size_t y, size_t x) {
    if (y > VGA_HEIGHT || x > VGA_WIDTH) {
        putchar_at('E', vga_color(RED, BLACK), VGA_HEIGHT-1, VGA_WIDTH-1);
        return;
    }

    uint16_t entry = vga_entry(ch, color);

    buffer[buffer_index(y, x)] = entry;
}

static void putchar(char ch, uint8_t color) {
    if (ch == '\n') {
        newline();
        return;
    }

    putchar_at(ch, color, current_row, current_col);

    if (current_col != VGA_WIDTH-1) current_col++;
    else newline();
}

uint8_t inline vga_color(enum Color bg, enum Color fg) {
    return fg | bg << 4;
}

void init_screen(void) {
    current_row = 0;
    current_col = 0;
    buffer = (uint16_t*) VGA_ADDRESS;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            buffer[buffer_index(y, x)] = vga_entry(' ', vga_color(BLACK, WHITE));
        }
    }
}

void kprint(const char *msg, uint8_t color) {
    int i = 0;
    while (msg[i] != '\0') {
        putchar(msg[i], color);
        i++;
    }
}
