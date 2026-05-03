#include "menu.h"
#include "main_menu.h"
#include "apps/paint/paint.h"
#include "terminal.h"
#include "libc/string.h"
#include "libc/stdbool.h"
#include "colors.h"

static int selected_item = 0;
#define NUM_OPTIONS 3

void test_action() {
    terminal_write("clicked 1st button", COLOR(BLUE, WHITE), 45, 16);
}

void test_actio3() {
    terminal_write("clicked 3rd button", COLOR(BLUE, WHITE), 45, 16);
}

struct button start_menu[] = {
    {"Print info", test_action},
    {"Paint program", enter_paint_program},
    {"Play game", test_actio3}
};

static void draw_buttons() {

    int num_buttons = sizeof(start_menu) / sizeof(start_menu[0]);
    int start_x = 30;
    int start_y = 10;

    for (int i = 0; i < num_buttons; i++) {
        bool is_selected = (i == selected_item);
        print_button(&start_menu[i], is_selected, start_x, start_y + i * 4);
    }
}

void handle_main_menu_keyboard(uint8 scancode) {
    switch (scancode) {
        case 0x11: // W
            selected_item = (selected_item - 1 + NUM_OPTIONS) % NUM_OPTIONS;
            break;
        case 0x1F: // S
            selected_item = (selected_item + 1) % NUM_OPTIONS;
            break;
        case 0x1C: // Enter
            start_menu[selected_item].action();
            return;
    }
    draw_buttons();
}

void enter_main_menu() {
    terminal_clear(0);
    draw_window("Main Menu");
    draw_buttons();
    current_menu = MAIN_MENU;
}