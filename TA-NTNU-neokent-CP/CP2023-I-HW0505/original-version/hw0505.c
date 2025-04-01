#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tas.h"

int main()
{
    char **tas_content = NULL;
    size_t size = 0;

    subtitle_set_frame(&tas_content, &size, "Hello from TA!", 1);
    subtitle_set_second(&tas_content, &size, "There's some examples I want to show you.", 3.5);
    subtitle_set_frame(&tas_content, &size, "Let's start by press T", 400);
    button_set_frame(&tas_content, &size, "T", 400, 400, 0);

    subtitle_set_frame(&tas_content, &size, "Here it's about at frame 600, I will jump(press A) at 700 to 730 frame", 600);
    button_set_frame(&tas_content, &size, "A", 700, 730, 0);

    subtitle_set_frame(&tas_content, &size, "And I jump(press A) only at 800", 750);
    button_set_frame(&tas_content, &size, "A", 800, 800, 0);

    subtitle_set_frame(&tas_content, &size, "Looks difference right? Jump high or low cause by the duration of pressing the A", 850);

    subtitle_set_second(&tas_content, &size, "Now it's passing about 20 seconds when you running emulator", 20);
    subtitle_set_second(&tas_content, &size, "I will running(press R, B) for 1.5 seconds and  running/jump for 1 seconds at 30th second.", 25);
    subtitle_set_second(&tas_content, &size, "Running and Jumping at second 30", 30);
    button_set_second(&tas_content, &size, "RB", 30, 32.5, 0);
    button_set_second(&tas_content, &size, "A", 31.5, 32.5, 0);

    demo(&tas_content, &size);
    tas_save((const char **)tas_content, size);
    
    // tas_read(&tas_content, &size);
    
    if (size) free(tas_content);

    return 0;
}