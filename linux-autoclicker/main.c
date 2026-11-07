#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>


#include "main.h"

int interval;
char WRInterrupt[256];

void simulate_click() {
    Display *display = XOpenDisplay(NULL);

    if (display == NULL) return;

    // 1 - LEFT CLICK, 2 - MIDDLE CLICK, 3 - RIGHT CLICKP
    // TRUE SPECIFIES PRESSING DOWN
    XTestFakeButtonEvent(display, 1, True, 0);
    XFlush(display);

    // EMULATE HUMAN CLICK
    usleep(1000);

    // FALSE SPECIFIES RELEASING THE BUTTON
    XTestFakeButtonEvent(display, 1, False, 0);
    XFlush(display);

    XCloseDisplay(display);
}

int main() {
    //
    start:

    printf("WELCOME TO LINUX-AUTOCLICKER\n");
    printf("ENTER CLICK INTERVAL: \n");

    scanf("%d", &interval);

    printf("CLICK INTERVAL OF %d SELECTED \n\n", interval);

    if (interval < 1) {
        //
        printf("INTERVAL INVALID OR 0, PLEASE TRY AGAIN\n\n");
        goto start;
    };

    bool running = true;

    while (running) {
        // AUTOCLICKER
        printf("CLICKED\n");
        simulate_click();
        // SLEEP
        usleep(interval * 1000);
    }

    return 0;
}