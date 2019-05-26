/** @file       screenlogic.c
    @author     Jaime Sequeira and Jack Taylor
    @date       17 October 2018
    @brief      Logic behind led map output
*/

#include "screenlogic.h"


/** Initialises display, then while button not pressed, calls draw_smiley_led ()  */
void happy_face (void)
{
    display_init ();
    button_update ();

    while (button_push_event_p(BUTTON1) == 0) {
        draw_smiley_led ();
        pacer_wait ();
        display_update ();
        button_update ();
    }

    button_update ();
}

/** Initialises display, then while button not pressed, calls draw_sad_led ()  */
void sad_face (void)
{
    display_init ();
    button_update ();

    while (button_push_event_p(BUTTON1) == 0) {
        draw_sad_led ();
        pacer_wait ();
        display_update ();
        button_update ();
    }

    button_update ();
}
