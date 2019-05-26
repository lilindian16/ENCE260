/** @file       screenoutput.c
    @author     Jaime Sequeira and Jack Taylor
    @date       17 October 2018
    @brief      Controls led map output
*/

#include "screenoutput.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 10
#define LOOP_RATE 1000
#define SCROLL_RATE 20


/** Takes single character and displays on board. */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/** Initialises the screen for scrolling text. */
void scroll_init (void)
{
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (SCROLL_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

/** Initialises the screen for solid images (e.g smiley face or single character). */
void solid_image_init (void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
}

/** Displays smiley face on led map. */
void draw_smiley_led (void)
{
    display_pixel_set (1, 0, 1);
    display_pixel_set (3, 0, 1);
    display_pixel_set (1, 1, 1);
    display_pixel_set (3, 1, 1);
    display_pixel_set (1, 2, 1);
    display_pixel_set (3, 2, 1);

    display_pixel_set (0, 4, 1);
    display_pixel_set (0, 5, 1);
    display_pixel_set (1, 6, 1);
    display_pixel_set (2, 6, 1);
    display_pixel_set (3, 6, 1);
    display_pixel_set (4, 5, 1);
    display_pixel_set (4, 4, 1);
}

/** Displays sad face on led map. */
void draw_sad_led (void)
{
    display_pixel_set (1, 0, 1);
    display_pixel_set (3, 0, 1);
    display_pixel_set (1, 1, 1);
    display_pixel_set (3, 1, 1);
    display_pixel_set (1, 2, 1);
    display_pixel_set (3, 2, 1);

    display_pixel_set (0, 6, 1);
    display_pixel_set (0, 5, 1);
    display_pixel_set (1, 4, 1);
    display_pixel_set (2, 4, 1);
    display_pixel_set (3, 4, 1);
    display_pixel_set (4, 5, 1);
    display_pixel_set (4, 6, 1);
}
