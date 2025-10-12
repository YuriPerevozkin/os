#include "drivers/vga/vga.h"
#include "drivers/tty.h"
#include <stdint.h>

void
kernel_entry() {
    init_tty();
    kprint("Hello, world!", vga_color(BLACK, GREEN));
}
