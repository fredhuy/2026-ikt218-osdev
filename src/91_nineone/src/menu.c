#include "menu.h"
#include "terminal.h"
#include "libc/string.h"
#include "colors.h"
#include "keyboard.h"

static int selected_item = 0;
static const char* options[] = {"PRINT DEBUG INFO", "PAINT", "WRITE TEXT"};

#define NUM_OPTIONS 3


static void menu_keyboard_handler(char character, uint8 scancode) {
    (void)character;

    switch (scancode) {
        case 0x11: // W
            selected_item = (selected_item - 1 + NUM_OPTIONS) % NUM_OPTIONS;
            terminal_write("W...", 0x0A, 30, 15);
            break;

        case 0x1F: // S
            selected_item = (selected_item + 1) % NUM_OPTIONS;
            terminal_write("S...", 0x0A, 30, 15);
            break;

        case 0x1C: // Enter
            terminal_write("Executing...", 0x0A, 30, 15);
            break;
    }
}

void menu_init() {
    draw();
    // Her skjer magien: Vi registrerer menyens egen handler til IRQ1 (tastatur)
    // IRQ1 er vanligvis interrupt 33 (32 + 1)
    keyboard_set_event_handler(menu_keyboard_handler);
}

void draw_window(const char* title) {
    uint8 attr = COLOR(YELLOW, BLUE);

    // Corners
    terminal_putchar(201, attr, 0, 0);                       // ╔
    terminal_putchar(187, attr, VGA_WIDTH - 1, 0);            // ╗
    terminal_putchar(200, attr, 0, VGA_HEIGHT - 1);            // ╚
    terminal_putchar(188, attr, VGA_WIDTH - 1, VGA_HEIGHT - 1); // ╝

    // Horisontal borders
    for (int x = 1; x < VGA_WIDTH - 1; x++) {
        terminal_putchar(205, attr, x, 0);              // ═
        terminal_putchar(205, attr, x, VGA_HEIGHT - 1); // ═
    }

    // Vertical borders
    for (int y = 1; y < VGA_HEIGHT - 1; y++) {
        terminal_putchar(186, attr, 0, y);              // ║
        terminal_putchar(186, attr, VGA_WIDTH - 1, y);  // ║
    }

    // Title
    terminal_write("\xB9", attr, 2, 0); // ╠
    terminal_write(title, COLOR(YELLOW, BLUE), 3, 0);
    terminal_write("\xCC", attr, 3 + strlen(title), 0); // ╣
}

void draw() {
    draw_window("Main Menu");
}