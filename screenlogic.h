/** @file    screenlogic.h
 @author     Jaime Sequeira and Jack Taylor
 @date       17 October 2018
 @brief      Logic behind led map output support
 */

#ifndef screenlogic_h
#define screenlogic_h

#include "system.h"
#include "tinygl.h"
#include "button.h"
#include "pacer.h"
#include "screenoutput.h"


/** Initialises display, then while button not pressed, sends command to draw smiley face. */
void happy_face (void);

/** Initialises display, then while button not pressed, sends command to draw sad face. */
void sad_face (void);


#endif /* screenlogic_h */
