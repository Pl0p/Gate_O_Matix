#include <Arduino.h>
#include <stdint.h>
#include <Keypad.h>

#include <Variables.h>
#include <Pinout.h>


/*
/!\ Erreur !!! J'ai inversé les lignes et les colonnes
    Sur le schéma kickad c'est 5row et 4col
    voir si ça fonctionne quand même 
*/

char keys[ROWS][COLS] = {
  {'a', 'b', 'c', 'd', '1'},
  {'e', 'f', 'g', 'h', '2'},
  {'i', 'j', 'k', 'l', '3'},
  {'m', 'n', 'o', 'p', '4'}
};
Keypad kpd = Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS );
uint8_t my_key;

bool shift = false;
bool stop = false;
bool copy = false;
bool fill = false;
bool save = false;

bool copied_state[ALL_STEP] = {0};
uint8_t which_step[7] = {0};

void inisialize_buttons (){

    pinMode(shift_pin, INPUT_PULLUP);

}

void handle_buttons_matrix () {

  for (byte i = 0; i < 7; ++i) {
  }

  if (kpd.getKeys()) // Si un boutton bouge
  {
    for (int i = 0; i < LIST_MAX; i++) // on stock son numéro dans une liste
    {
      if (kpd.key[i].stateChanged) { // selon quelle boutton bouge
        my_key = kpd.key[i].kchar;

        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:

            if (my_key > 96 && my_key < 113) {

              if (shift == false) {

                step_state[selected_part][my_key - 97 + page_pos * 16] = !step_state[selected_part][my_key - 97 + page_pos * 16];

                if (i < 6) {
                  which_step[i] = (my_key - 97) + page_pos * 16; // the 6 last step who has changed
                }


              } else if (shift == true) { // jump the step
                step_to_jump[my_key - 97 + page_pos * 16] = !step_to_jump[my_key - 97 + page_pos * 16];
              }
            }
            switch (my_key) {
              case 49 :
                pause = !pause;
                stop = true;
                break;
              case 50 :
                copy = true;
                break;
              case 51 :
                fill = true;
                break;
              case 52 :
                save = true;
                break;
            }
            break;

          case RELEASED :
            switch (my_key) {
              case 49 :
                stop = false;
                break;
              case 50 :
                copy = false;
                break;
              case 51 :
                fill = false;
                break;
              case 52 :
                save = false;
                break;
            }
          break;
        }
      }
    }
  }
}

void handle_shift_button(){

  shift = !digitalRead(shift_pin);

  if (!shift) { //_________________ sans le SHIFT

    if (!pause) {
      //Serial.println("play");
      play = true;
    } else if (pause) {
      //Serial.println("paused");
      play = false;
    }

    if (copy)
    {
      //Serial.println("Copied");
      for (int i = 0; i < ALL_STEP; ++i) {
        copied_state[i] = step_state[selected_part][i];              // On copie les états de la voie actuelle
      }
    }

    if (fill) {
      //Serial.println("Filled");
      step_state[selected_part][actual_step[selected_part]] = 1;            // On copie les états de la voie actuelle
    }

    if (save) {
      //Serial.println("Saved");
    }

  } else if (shift) { //_________________ Avec le SHIFT

    if (stop) {
      //Serial.println("stoped");
      play = false;
      pause = true;
      for (int i = 0; i < ALL_PART; ++i) {
        actual_step[i] = 0;
      }
    }

    if (copy)
    {
      //Serial.println("pasted");
      for (int i = 0; i < ALL_STEP; ++i)
      {
        step_state[selected_part][i] = copied_state[i];              // On colle les états de la voie actuelle
      }
    }

    if (fill) {
      //Serial.println("cleared");
      for (int i = 0; i < ALL_STEP; ++ i) {
        step_state[selected_part][i] = 0;
      }
    }

    if (save) {
      //Serial.println("loaded");
    }
  }
}