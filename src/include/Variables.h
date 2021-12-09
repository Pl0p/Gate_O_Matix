#pragma once

#include <Arduino.h>
#include <stdint.h>

#define ALL_STEP 64
#define ALL_PART 8

/* For the buttons matrix */
#define ROWS 4
#define COLS 5

/* Generals variables */

extern uint8_t BPM;
extern bool clock;

extern bool play;
extern bool pause;

extern uint8_t page_pos;
extern uint8_t selected_part;


extern uint8_t number_of_step[ALL_PART];
extern uint8_t actual_step[ALL_PART];
extern bool step_state[ALL_PART][ALL_STEP];
extern unsigned long step_start;
extern float step_length;

extern bool step_to_jump [ALL_STEP];
extern uint8_t which_way;


/*For the screen*/
extern uint8_t which_encoder;
extern uint8_t which_parameter;
extern uint8_t which_mode;
extern uint8_t which_part_param;
extern uint8_t which_step_param;




