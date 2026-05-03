#include "paint.h"
#include "menu.h"
#include "main_menu.h"
#include "terminal.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/stdbool.h"
#include "arch/i386/isr.h"
#include "colors.h"

static int selected_item = 0;
#define NUM_OPTIONS 3

void test_actio2() {
    terminal_write("clicked 2nd button", COLOR(BLUE, WHITE), 45, 16);
}

struct button paint_menu[] = {
    {"Return", test_actio2},
    {"Save", test_actio2},
    {"Exit", enter_main_menu}
};

static void draw_buttons() {

    int num_buttons = sizeof(paint_menu) / sizeof(paint_menu[0]);
    int start_x = 60;
    int start_y = 10;

    for (int i = 0; i < num_buttons; i++) {
        bool is_selected = (i == selected_item);
        print_button(&paint_menu[i], is_selected, start_x, start_y + i * 4);
    }
}

void handle_paint_keyboard(uint8 scancode) {
    switch (scancode) {
        case 0x11: // W
            selected_item = (selected_item - 1 + NUM_OPTIONS) % NUM_OPTIONS;
            break;
        case 0x1F: // S
            selected_item = (selected_item + 1) % NUM_OPTIONS;
            break;
        case 0x1C: // Enter
            paint_menu[selected_item].action();
            return;
    }
    switch (selected_item) {
        case 0:
            terminal_write("selected: 0", COLOR(LIGHT_GREY, BLACK), 3, 21);
            break;
        case 1:
            terminal_write("selected: 1", COLOR(LIGHT_GREY, BLACK), 3, 21);
            break;
        case 2:
            terminal_write("selected: 2", COLOR(LIGHT_GREY, BLACK), 3, 21);
            break;
        default:
            terminal_write("selected: ?", COLOR(LIGHT_GREY, BLACK), 3, 21);
    }
    draw_buttons();
}

void enter_paint_program() {
    terminal_clear();
    draw_window("Paint Program");
    draw_buttons();
    current_menu = PAINT_MENU;
}