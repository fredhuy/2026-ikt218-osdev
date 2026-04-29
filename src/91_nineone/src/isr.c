#include "isr.h"
#include "idt.h"

#include "terminal.h"

static int isr_line = 0;

static void isr_print(const char* str) {
    terminal_write(str, 0x0F, 0, isr_line);
}

static void print_interrupt_number(uint32_t n) {
    if (n == 0) {
        isr_print("0");
    } else if (n == 1) {
        isr_print("1");
    } else if (n == 2) {
        isr_print("2");
    } else if (n == 3) {
        isr_print("3");
    } else {
        isr_print("unknown");
    }
}




void isr_handler(registers_t* regs) {
    terminal_write("Interrupt triggered: ", 0x0F, 0, isr_line);
    terminal_write("   ", 0x0F, 21, isr_line); // clears old number area

    if (regs->int_no == 0) {
        terminal_write("0", 0x0F, 21, isr_line);
        } else if (regs->int_no == 1) {
            terminal_write("1", 0x0F, 21, isr_line);
        } else if (regs->int_no == 2) {
            terminal_write("2", 0x0F, 21, isr_line);
        } else if (regs->int_no == 3) {
            terminal_write("3", 0x0F, 21, isr_line);
        }

    isr_line++;

    if (isr_line >= VGA_HEIGHT) {
        isr_line = 0;
    }
}