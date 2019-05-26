/** @file    screenoutput.h
 @author     Jaime Sequeira and Jack Taylor
 @date       17 October 2018
 @brief      Led map output support
 */

#ifndef screenoutput_h
#define screenoutput_h

#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


/** Takes single character and displays on board. */
void display_character (char character);

/** Initialises the screen for scrolling text. */
void scroll_init (void);

/** Initialises the screen for solid images (e.g smiley face or single character). */
void solid_image_init (void);

/** Displays smiley face on led map. */
void draw_smiley_led (void);

/** Displays sad face on led map. */
void draw_sad_led (void);


#endif /* screenoutput_h */
