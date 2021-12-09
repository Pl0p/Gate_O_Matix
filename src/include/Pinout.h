#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <Variables.h>

/* Encoder 1 pinout */
#define general_SW_pin 2
#define general_inputCLK 3
#define general_inputDT 4
#define general_led_pin A7

/* Encoder 2 pinout */
#define per_part_SW_pin A6
#define per_part_inputCLK A4
#define per_part_inputDT A5
#define per_part_led_pin A3

/* Encoder 3 pinout */
#define data_SW_pin 36
#define data_inputCLK 34
#define data_inputDT 35
#define data_led_pin 37


/* Button matrix pinout */
extern const uint8_t rowPins[ROWS] = {42, 43, 44, 45}; //connect to the row pinouts of the buttons matrix
extern const uint8_t colPins[COLS] = {49, 50, 51, 52, 53}; //connect to the column pinouts of the buttons matrix

/* Seven segment pinout */
uint8_t digitPins[] = {22, 23, 24}; // 1 2 3
uint8_t segmentPins[] = {25, 26, 27, 28, 29, 30, 31}; // A B C D E F G

/* To shift registers pinout */
//---------------------Step Led--------------------------
#define verrou 11    //LATCH PIN
#define horloge 12   //CLOCK PIN
#define data 10      //DATA  PIN

//---------------------Tempo Led--------------------------
#define verrou2 6    //LATCH PIN
#define horloge2 5   //CLOCK PIN
#define data2 7      //DATA  PIN


/* Selector pinout */
#define selectorPin A0

/* Reset pinout */
#define reset_pin 8

/* Shifth pinout */
#define shift_pin A2

/*Gate's output pinout*/
extern const uint8_t gate_out_pin[ALL_PART] = {A8, A9, A10, A11, A12, A13, A14, A15};
