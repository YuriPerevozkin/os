#include <stdint.h>
#include <stddef.h>
#include "vga.h"

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
