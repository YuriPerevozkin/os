#include "drivers/screen.h"

void kernel_entry() {
    clear_screen();
    kprint("Hello, World!");
}
