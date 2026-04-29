#include "terminal.c"
#include "colors.h"
#define terminal_write print

int main() {
    init_gdt();
    print("Velkommen til FreDDaviDOS!", COLOR(YELLOW, BLUE), 0, 0);

    while (1) { // coming soon
    }

    return 0;
}