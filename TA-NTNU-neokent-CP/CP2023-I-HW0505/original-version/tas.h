#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
    Set NES button within fm2 file content by frame range.

    Parameters: 
        src: The source from fm2 file content.
        size: src size for pointer.
        button: Button string to set. (Order doesn't matter)
        start_frame: Represent start frame to set button.
        end_frame: Represent end frame to set button.
        unset: If true, clear button but not delete it. Otherwise, as above description.

    Examples:
        Set R and B button from frame 381 to frame 480.
        
        $ button_set_frame(src, size, "RB", 381, 480, 0);

    Note:
        If the frame range is overflow, please increase the size of src automatically
*/
void button_set_frame(char ***src, size_t *size, const char *button, const uint64_t start_frame, const uint64_t end_frame, const bool unset);

/*
    Set NES button within fm2 file content by second range.

    Parameters: 
        src: The source from fm2 file content.
        size: src size for pointer.
        button: Button string to set. (Order doesn't matter)
        start_sec: Represent start second to set button.
        end_sec: Represent end second to set button.
        unset: If true, clear button but not delete it. Otherwise, as above description.
    
    Examples:
        Set L, B, and A button from 5.5 seconds to 15.232 seconds.
        
        $ button_set_second(src, size, "LBA", 5.5, 15.232, 0);
    
    Note:
        If the second range is overflow, please increase the size of src automatically

*/
void button_set_second(char ***src, size_t *size, const char *button, const double start_sec, const double end_sec, const bool unset);

/*
    Set subtitle within fm2 file content by specific frame.

    Parameters: 
        src: The source from fm2 file content.
        size: src size for pointer.
        subtitle: Subtitle string to set.
        frame: Set subtitle at specific frame.

    Examples:
        Set "Start Speed Run!!" subtitle string at frame 0.

        $ button_set_frame(src, size, "Start Speed Run!!", 0);
*/
void subtitle_set_frame(char ***src, size_t *size, const char *subtitle, const uint64_t frame);

/*
    Set subtitle within fm2 file content by specific second.

    Parameters: 
        src: The source from fm2 file content.
        size: src size for pointer.
        subtitle: Subtitle string to set.
        second: Set subtitle at specific second.

    Examples:
        Set "1-1 clear!!" subtitle string at 55.413 seconds.
        
        $ button_set_frame(src, size, "1-1 clear!!", 55.413);
*/
void subtitle_set_second(char ***src, size_t *size, const char *subtitle, const double second);

/*
    Read from fm2 file source.

    Parameters: 
        src: The pointer to store fm2 file content.
        size: src size for pointer.
    
    Note:
        No matter the origin of src, src will be replaced by new fm2 file source.
*/
void tas_read(char*** src, size_t *size);

/*
    Save fm2 file source

    Parameters: 
        src: The source from fm2 file content.
        size: src size for pointer.
*/
void tas_save(const char** src, const size_t size);

/*
    Set 1-1 map clear step fm2 content to src

    Parameters: 
        src: The source from fm2 file content.
        size: src size for pointer.
    
    Note:
        - This function should be implement by the other function.
        - No matter the origin of src, src will be replaced by demo content.
*/
void demo(char*** src, size_t *size);