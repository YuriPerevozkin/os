#include "drivers/screen.h"

void kernel_entry() {
    uint8_t color = vga_color(BLACK, GREEN);

    init_screen();
    kprint("Hello, world!\n", color);
}
