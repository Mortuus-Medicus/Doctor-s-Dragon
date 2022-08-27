//Created by Doctor


#ifndef KEYBOARD_READER_H
#define KEYBOARD_READER_H

#include "graphics.h"

#define ARROW_LEFT 0x25
#define ARROW_UP 0x26
#define ARROW_RIGHT 0x27
#define ARROW_DOWN 0x28

int getch_noblock() {
    if (kbhit())
        return getch();
    else
        return -1;
}

//To se uporablja za branje tipkovnice
//GetAsyncKeyState();

#endif
