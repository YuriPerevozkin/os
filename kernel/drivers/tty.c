#include <stdint.h>
#include <stddef.h>
#include "vga/vga.h"

static size_t current_row;
static size_t current_col;
static volatile uint16_t* buffer;

static void
newline() {
    if (current_row != VGA_HEIGHT-1) {
        ++current_row;
        current_col = 0;
    }
}

void
init_tty() {
    current_row = 0;
    current_col = 0;
    buffer = init_buffer();

    if (cursor_enabled()) {
        toggle_cursor();
    }
}

void
putchar_at(unsigned char ch, uint8_t color, size_t y, size_t x) {
    if (y > VGA_HEIGHT || x > VGA_WIDTH) {
        putchar_at('E', vga_color(RED, BLACK), VGA_HEIGHT-1, VGA_WIDTH-1);
        return;
    }

    buffer[buffer_index(y, x)] = vga_entry(ch, color);
}

void
putchar(unsigned char ch, uint8_t color) {
    if (ch == '\n') {
        newline();
        return;
    }
    if (ch == '\t') {
        for(int i = 0; i < 4; ++i) {
            putchar(' ', color);
        }
        return;
    }

    putchar_at(ch, color, current_row, current_col);

    if (current_col != VGA_WIDTH-1) {
        ++current_col;
    } else {
        newline();
    }
}

void
kprint(const char* msg, uint8_t color) {
    while (*msg != '\0') {
        putchar(*msg, color);
        ++msg;
    }
}
