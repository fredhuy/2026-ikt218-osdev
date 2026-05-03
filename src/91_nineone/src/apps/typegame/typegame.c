#include "include/apps/typegame/typegame.h"
#include "include/libc/stdbool.h"

static const char* text = "welcome to typegame. this is the first ever sentence."
static int current_index = 0;
static int mistakes = 0;
static bool isRunning = false;



void typegame_start() 
{
    current_index = 0;
    mistakes = 0;
    isRunning = true;


    // Clear screen
    // Draw
    // Start timer

}
void typegame_update()
{
    // Update timer
    // Update other UI (wpm)
    // 
}

void typegame_handle_key(char c)
{

}

static void typegame_end() 
{

}

static void typegame_draw() 
{

}
