#include <stdint.h>
#include "../io.h"
#include "vga.h"

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
