/*
   MIT License

   Copyright (c) 2025 Perevozkin Yuri

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <stdint.h>
#include <stddef.h>
#include <kernel/vga.h>

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
