#include "terminal.h"
#include "colors.h"
#include "gdt.h"

int main() {
    init_gdt();
    terminal_write("Velkommen til FreDDaviDOS!", COLOR(YELLOW, BLUE), 0, 0);

    while (1) { // coming soon
    }

    return 0;
}