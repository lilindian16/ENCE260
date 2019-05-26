/* Paper Scissors Rock Game for UCFK4
 * ENCE260 Embedded Systems Assignment
 * Authors: Jack Taylor and Jaime Sequeira
 * Student ID: 87836665 and 42408823
 * 17/10/2018
 */

#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "led.h"
#include "pio.h"
#include "timer.h"
#include "screenoutput.h"
#include "screenlogic.h"

#define PACER_RATE 1000


unsigned int choosing_language (void)
/* PLAYER USES NAV KEYS TO CHOOSE THEIR LANGUAGE AND SELECTS IT BY PRESSING NAVSWITCH.
 * Returns unsigned int, 0 for English and 1 for Espanol
 */
{
    scroll_init ();

    unsigned int index = 0;
    unsigned int last_language = 1;
    unsigned int first_language = 0;
    char words[2][10] = {
                            "ENGLISH",
                            "ESPANOL",
                        };
    char* word = words[index];
    tinygl_text (word);

    navswitch_update ();

    while (navswitch_push_event_p(NAVSWITCH_PUSH) == 0) {
        pacer_wait ();
        tinygl_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if ( index < last_language ) {
                index++;
                word = words[index];
                tinygl_clear ();
                tinygl_text (word);
            } else {
                index = first_language;
                word = words[index];
                tinygl_clear ();
                tinygl_text (word);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (index > first_language) {
                index--;
                word = words[index];
                tinygl_clear ();
                tinygl_text (word);
            } else {
                index = last_language;
                word = words[index];
                tinygl_clear ();
                tinygl_text (word);
            }
        }
        navswitch_update ();
    }
    return index;
}

void starting_screen (unsigned int language)
/*THE OPENING PROMPT TO START THE GAME WITH SCROLLING MESSAGE. THE 
 * INTEGER INPUT DETERMINES WHAT LANGUAGE TO DISPLAY, 0 FOR ENG AND 1 
 * FOR ESP
 */
{
    unsigned int english_binary = 0;
    
    scroll_init (); 
    
    if (language == english_binary) {
        tinygl_text ("PRESS TO START");
    } else {
        tinygl_text ("HAZ CLIC PARA EMPEZAR");
    }

    navswitch_update ();

    while (navswitch_push_event_p(NAVSWITCH_PUSH) == 0) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }

    navswitch_update ();

}


void winning_screen (unsigned int language)
/*DISPLAYS TEXT 'WINNER' ON LED MAT UNTIL BUTTON CLICKED. INTEGER INPUT
 * DETERMINES OUTPUT DISPLAY LANGUGE AS PREVIOUS.
 */

{
    unsigned int english_binary = 0;
    
    scroll_init ();

    if (language == english_binary) {
        tinygl_text ("WINNER! ");
    } else {
        tinygl_text ("MUY BIEN!");
    }

    button_update ();

    while (button_push_event_p(BUTTON1) == 0) {
        pacer_wait ();
        tinygl_update ();
        button_update ();
    }
}

void losing_screen (unsigned int language)
/*DISPLAYS TEXT 'LOSER' ON LED MAT UNTIL BUTTON CLICKED. INTEGER INPUT
 * DETERMINES DISPLAY LANGUAGE AS PREVIOUS
 */
{
    scroll_init ();
    unsigned int english_binary = 0;
    
    if(language == english_binary) {
        tinygl_text ("LOSER! ");
    } else {
        tinygl_text ("MIERDA!");
    }

    button_update ();

    while (button_push_event_p(BUTTON1) == 0) {
        pacer_wait ();
        tinygl_update ();
        button_update ();
    }
}

unsigned int number_games (void)
//PLAYER USES NAV KEYS TO CHOOSE THE NUMBER OF GAMES
{
    unsigned int number;
    unsigned int i = 0;
    unsigned int last_index = 2;
    unsigned int first_index = 0;
    char characters[4] = {'1', '3', '5', '\0'};
    char character = characters[i];

    solid_image_init ();
    button_update ();
    navswitch_update ();

    while (button_push_event_p(BUTTON1) == 0) {

        tinygl_update ();
        button_update ();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if ( i<last_index ) {
                i++;
                character = characters[i];
            }
        }


        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if ( i>first_index ) {
                i--;
                character = characters[i];
            }
        }

        display_character (character);
        pacer_wait ();
    }

    if (character == '1') {
        number = 1;
    } else if (character == '3') {
        number = 3;
    } else {
        number = 5;
    }
    return number;
}

char choosing_attack (int language)
/*PLAYER USES NAV KEYS TO CHOOSE THEIR CHARACTER. FUNCTION RETURNS CHARACTER
 * TO BE USED FOR GAME LOGIC AS CHAR. INPUT INT DETERMINES LANGUE DISPLAY
 * AS PREVIOUSLY STATED.
 */
{
    unsigned int index = 0;
    unsigned int first_index = 0;
    unsigned int last_index = 2;
    unsigned int spanish_index = 3;
    signed int english_binary = 0;
    signed int spanish_binary = 1;
    char words[6][10] = {
        "PAPER",
        "SCISSORS",
        "ROCK",
        "PAPEL",
        "TIEJRAS",
        "ROCA"
    };

    scroll_init ();

    if (language == spanish_binary) {
        index = 3; //Make list of words start at Spanish
    }
    char* word = words[index];
    tinygl_text (word);

    char characters[4] = {'P', 'S', 'R', '\0'};
    char character = characters[index];


    button_update ();
    navswitch_update ();

    while (button_push_event_p(BUTTON1) == 0) {
        pacer_wait ();
        tinygl_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (index<last_index) {
                index++;
                if (language == english_binary) {
                    word = words[index];
                } else {
                    word = words[index + spanish_index];
                }
                tinygl_clear ();
                tinygl_text (word);
                character = characters[index];
            } else {
                index = first_index;
                if (language == english_binary) {
                    word = words[index];
                } else {
                    word = words[index + spanish_index];
                }
                tinygl_clear ();
                tinygl_text (word);
                character = characters[index];
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (index>first_index) {
                index--;
                if (language == english_binary) {
                    word = words[index];
                } else {
                    word = words[index + spanish_index];
                }
                tinygl_clear ();
                tinygl_text (word);
                character = characters[index];
            } else {
                index = last_index;
                if (language == english_binary) {
                    word = words[index];
                } else {
                    word = words[index + spanish_index];
                }
                tinygl_clear ();
                tinygl_text (word);
                character = characters[index];
            }
        }
        navswitch_update ();
        button_update ();
    }
    return character;
}

char ir_communicate (char chosen_character, unsigned int language)
/*CONSTANTLY CHECKS FOR CHARACTER BEING SENT VIA IR. 
 * SENDS ON THE CLICK OF BUTTON AND THEN RETURNS OPPONENT CHARACTER AS
 * CHAR. INPUT
 */
{
    unsigned int enlgish_binary = 0;
    char character = '\0';
    unsigned int sent = 0;
    unsigned int received = 0;
    
    scroll_init ();
    button_update ();
    
    if (language == enlgish_binary) {
        tinygl_text ("CLICK TO SEND ");
    } else {
        tinygl_text ("HAZ CLIC PARA ENVIAR");
    }

    while (sent == 0 || received == 0) {
        navswitch_update ();
        tinygl_update ();
        pacer_wait ();
        button_update ();

        if (ir_uart_read_ready_p ()) {
            character = ir_uart_getc ();
            if (character != '\0') {
                received = 1;
            }
        }

        if (button_push_event_p(BUTTON1) && sent == 0 ) {
            ir_uart_putc (chosen_character);
            if (language == 0) {
                tinygl_text ("WAITING ");
            } else {
                tinygl_text ("ESPERATE");
            }
            tinygl_update ();
            sent = 1;
        }
    }
    ir_uart_putc (chosen_character);
    return character;
}

unsigned int get_result (char chosen, char opponent)
/*LOGIC OF GAME, WORKS OUT WHO WINS LOSES AND DRAWS. RETURNS A 1 IF 
 * PLAYER LOSES ROUND, A 2 IF THE GAME IS A TIE AND 3 IF PLAYER WINS
 */
{
    unsigned int result;
    if (chosen == opponent) {
        result = 2;
    } else if (chosen == 'P') {
        if (opponent == 'S') {
            result = 1;
        } else {
            result = 3;
        }
    } else if (chosen == 'S') {
        if (opponent == 'R') {
            result = 1;
        } else {
            result = 3;
        }
    } else {
        if (opponent == 'P') {
            result = 1;
        } else {
            result = 3;
        }
    }
    return result;
}

int main (void)
{
    system_init ();
    navswitch_init ();
    pacer_init (PACER_RATE);
    ir_uart_init ();
    led_init ();
    led_set (LED1, 0);
    button_init ();
    unsigned int language = choosing_language ();

    while (1) {
        
        led_set (LED1, 0);
        starting_screen (language);
        button_update();
        unsigned int player_score = 0;
        unsigned int opponent_score = 0;
        unsigned int best_of = number_games();
        unsigned int to_win = (best_of+1)/2;
        unsigned int game = 1;
        unsigned int loss = 1;
        unsigned int win = 3;
        unsigned int turn_led_on = 1;

        while (game <= best_of && (player_score < to_win && opponent_score < to_win)) {

            char chosen_char = choosing_attack (language);
            char opponent_char = ir_communicate (chosen_char, language);
            unsigned int match_result = get_result (chosen_char, opponent_char);

            if (match_result == loss) {
                opponent_score++;
                game++;
                sad_face ();
            } else if (match_result == win) {
                player_score++;
                game++;
                happy_face();
            }

            if (player_score == to_win) {
                led_set (LED1, turn_led_on);
                winning_screen (language);
            } else if (opponent_score == to_win) {
                losing_screen (language);
            }
        }

    }

    return 0;
}
