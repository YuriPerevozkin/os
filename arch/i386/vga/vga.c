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

uint8_t
cursor_enabled() {
    return !get_bit(read_crtc_reg(CURSOR_START), 5); // 0 - enabled. Invert logic
}

void
toggle_cursor() {
    write_crtc_reg(CURSOR_START, read_crtc_reg(CURSOR_START) ^ (1 << 5));
}

volatile uint16_t*
init_buffer() {
    uint16_t* buffer = (uint16_t*) VGA_ADDRESS_TEXT;

    for (size_t y = 0; y < VGA_HEIGHT; ++y) {
        for (size_t x = 0; x < VGA_WIDTH; ++x) {
            buffer[buffer_index(y, x)] = vga_entry(' ', vga_color(BLACK, WHITE));
        }
    }

    return buffer;
}
