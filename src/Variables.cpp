#include <Arduino.h>
#include <stdint.h>

#include <Variables.h>
#include <Pinout.h>

uint8_t BPM;
bool clock;

bool play;
bool pause = false;

uint8_t page_pos;
uint8_t selected_part;

uint8_t number_of_step[ALL_PART];
uint8_t actual_step[ALL_PART];
bool step_state[ALL_PART][ALL_STEP] = {0};
unsigned long step_start;
float step_length;

bool step_to_jump [ALL_STEP];
uint8_t which_way;

uint8_t which_encoder;
uint8_t which_parameter;
uint8_t which_mode;
uint8_t which_part_param;
uint8_t which_step_param;



byte delays;
byte swing;
byte gate_rate[ALL_PART];


bool inverted_state[ALL_PART];

byte probability[ALL_STEP];
byte racheting[ALL_STEP][4]; // 4 mode de racheting
byte step_gate_rate[ALL_STEP];

//---------------------Le temps--------------------------






int gate_length[ALL_PART];

unsigned long lastDebounceTime = 0;   // For the encoders buttons






