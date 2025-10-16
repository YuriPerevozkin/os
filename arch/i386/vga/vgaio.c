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
#include "../io.h"
#include <kernel/vga.h>

uint8_t
read_attribute_reg(enum attribute_register reg) {
    inb(INPUT_STATUS_1);
    outb((1 << 5) | reg, ATTRIBUTE_ADDRESS);
    return inb(ATTRIBUTE_DATA);
}

void
write_attribute_reg(enum attribute_register reg, uint8_t value) {
    inb(INPUT_STATUS_1);
    outb((1 << 5) | reg, ATTRIBUTE_ADDRESS);
    outb(value, ATTRIBUTE_ADDRESS);
}

uint8_t
read_sequencer_reg(enum sequencer_register reg) {
    outb(reg, SEQUENCER_ADDRESS);
    return inb(SEQUENCER_DATA);
}

void
write_sequencer_reg(enum sequencer_register reg, uint8_t value) {
    outb(reg, SEQUENCER_ADDRESS);
    outb(value, SEQUENCER_DATA);
}

uint8_t
read_graphics_reg(enum graphics_register reg) {
    outb(reg, GRAPHICS_ADDRESS);
    return inb(GRAPHICS_DATA);
}

void
write_graphics_reg(enum graphics_register reg, uint8_t value) {
    outb(reg, GRAPHICS_ADDRESS);
    outb(value, GRAPHICS_DATA);
}

uint8_t
read_crtc_reg(enum crtc_register reg) {
    outb(reg, CRTC_ADDRESS);
    return inb(CRTC_DATA);
}

void
write_crtc_reg(enum crtc_register reg, uint8_t value) {
    outb(reg, CRTC_ADDRESS);
    outb(value, CRTC_DATA);
}
