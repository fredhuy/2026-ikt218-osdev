#pragma once

#include "libc/stdint.h"
#include "libc/stddef.h"

#define T 125


// One note in the song. frequency of 0 is slient
typedef struct {
    uint32_t frequency;
    uint32_t duration;
} Note;

// A song is stored as a list of notes plus the number of notes to play.
typedef struct Song {
    Note* notes;
    size_t note_count;
} Song;


// Notes for attempt at "Song of Storms" (Love Zelda). Each entry is {frequency in Hz, duration in ms}.
static Note music_1[] = {

    {147,   T*4}, // D3
    {294, T},  // D4
    {349, T},  // F4
    {587, T*6},  // D5


    {294, T},  // D4
    {349, T},  // F4
    {587, T*6},  // D5


    {659, T*3},  // E5
    {698, T},  // F5
    {659, T},  // E5
    {698, T},  // F5
    {659, T},  // E5
    {523, T},  // C5
    {440, T*4},  // A4
    {0,   T*2},
    

    {440, T*2},  // A4
    {294, T*2},  // D4
    {349, T},  // F4
    {392, T},  // G4
    {440, T*4},  // A4
    {0,   T*2},
    
    {440, T*2},  // A4
    {294, T*2},  // D4
    {349, T},  // F4
    {392, T},  // G4
    {330, T*6},  // her tar jeg en vbri og bruker E4 som har frekvensen ]
    {0,   T*2},
};