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

#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>

#define VGA_ADDRESS_TEXT 0xb8000
#define VGA_ADDRESS_12H 0xa0000
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

enum vga_port {
    ATTRIBUTE_ADDRESS = 0x3c0,
    ATTRIBUTE_DATA = 0x3c1,
    INPUT_STATUS_0 = 0x3c2,
    SEQUENCER_ADDRESS = 0x3c4,
    SEQUENCER_DATA = 0x3c5,
    GRAPHICS_ADDRESS = 0x3ce,
    GRAPHICS_DATA = 0x3cf,
    CRTC_ADDRESS = 0x3d4,
    CRTC_DATA = 0x3d5,
    INPUT_STATUS_1 = 0x3da,
};

enum attribute_register {
    ATTRIBUTE_MODE_CONTROL = 0x10,
    OVERSCAN_COLOR,
    COLOR_PLANE_ENABLE,
    HORIZONTAL_PIXEL_PANNING,
    COLOR_SELECT,
};

enum sequencer_register {
    RESET,
    CLOCKING_MODE,
    MAP_MASK,
    CHARACTER_MAP_SELECT,
    SEQUENCER_MEMORY_MODE,
};

enum graphics_register {
    SET_RESET,
    ENABLE_SET_RESET,
    COLOR_COMPARE,
    DATA_ROTATE,
    READ_MAP_SELECT,
    GRAPHICS_MODE,
    MISC_GRAPHICS,
    COLOR_DONT_CARE,
    BIT_MASK,
};

enum crtc_register {
    HORIZONTAL_TOTAL,
    END_HORIZONTAL_DISPLAY,
    START_HORIZONTAL_BLANKING,
    END_HORIZONTAL_BLANKING,
    START_HORIZONTAL_RETRACE,
    END_HORIZONTAL_RETRACE,
    VERTICAL_TOTAL,
    OVERFLOW,
    PRESET_ROW_SCAN,
    MAXIMUM_SCAN_LINE,
    CURSOR_START,
    CURSOR_END,
    START_ADDRESS_HIGH,
    START_ADDRESS_LOW,
    CURSOR_LOCATION_HIGH,
    CURSOR_LOCATION_LOW,
    VERTICAL_RETRACE_START,
    VERTICAL_RETRACE_END,
    VERTICAL_DISPLAY_END,
    OFFSET,
    UNDERLINE_LOCATION,
    START_VERTICAL_BLANKING,
    END_VERTICAL_BLANKING,
    CRTC_MODE_CONTROL,
    LINE_COMPARE,
};

enum color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

static inline uint8_t
get_bit(uint8_t byte, uint8_t index) {
    return byte & (1 << index);
}

static inline uint8_t
vga_color(enum color bg, enum color fg) {
    return fg | bg << 4;
}

static inline uint16_t
vga_entry(char ch, uint8_t color) {
    return (uint16_t) ch | color << 8;
}

static inline size_t
buffer_index(size_t y, size_t x) {
    return y * VGA_WIDTH + x;
}

// vga.c
volatile uint16_t* init_buffer();
void switch_to_mode_13h();
uint8_t cursor_enabled();
void toggle_cursor();

// vgaio.c
uint8_t read_attribute_reg(enum attribute_register reg);
void write_attribute_reg(enum attribute_register reg, uint8_t value);
uint8_t read_sequencer_reg(enum sequencer_register reg);
void write_sequencer_reg(enum sequencer_register reg, uint8_t value);
uint8_t read_graphics_reg(enum graphics_register reg);
void write_graphics_reg(enum graphics_register reg, uint8_t value);
uint8_t read_crtc_reg(enum crtc_register reg);
void write_crtc_reg(enum crtc_register reg, uint8_t value);

#endif
