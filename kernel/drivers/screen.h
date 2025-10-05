#include <stdint.h>
#include <stddef.h>
#define VGA_ADDRESS 0xb8000
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

enum Color {
    BLACK = 0x0,
    BLUE = 0x1,
    GREEN = 0x2,
    CYAN = 0x3,
    RED = 0x4,
    MAGENTA = 0x5,
    BROWN = 0x6,
    LIGHT_GREY = 0x7,
    DARK_GREY = 0x8,
    LIGHT_BLUE = 0x9,
    LIGHT_GREEN = 0xa,
    LIGHT_CYAN = 0xb,
    LIGHT_RED = 0xc,
    LIGHT_MAGENTA = 0xd,
    YELLOW = 0xe,
    WHITE = 0xf,
};

uint8_t vga_color(enum Color bg, enum Color fg);
void kprint(const char *msg, uint8_t color);
void init_screen();
