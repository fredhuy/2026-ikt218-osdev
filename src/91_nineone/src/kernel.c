#include "terminal.h"
#include "colors.h"
#include "gdt.h"
#include "idt.h"

int main() {
    init_gdt();
    terminal_write("Velkommen til FreDDaviDOS!", COLOR(YELLOW, BLUE), 0, 0);


    idt_init();
    terminal_write("IDT loaded", COLOR(WHITE, BLACK), 0, 1);

    asm volatile("int $0x3");

    terminal_write("After interrupt", COLOR(WHITE, BLACK), 0, 3);


    while (1) { // coming soon
    }

    return 0;
}