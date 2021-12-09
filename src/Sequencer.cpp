#include <Arduino.h>
#include <stdint.h>

#include <Variables.h>
#include <Pinout.h>


void the_clock() {
/*
Need to remake a clock who give a correct step lenght
*/
}

void reset() {

  unsigned long lastTime;
  bool reset_state;
  bool last_reset_state = false;

  int reading = digitalRead(reset_pin);
  if (reading != last_reset_state) {
    lastTime = millis();
  }

  if ((millis() - lastTime) > 5) {

    if (reading != reset_state) {
      reset_state = reading;


      if (reset_state == HIGH) {
        for (int i = 0; i < ALL_PART; ++i) {
          actual_step[i] = 0;
        }
      }
    }
  }
  last_reset_state = reading;
}

void next_step() {

  bool ping[ALL_PART] = {1};

  switch (which_way) {

    case 0 : // forward

      for (int i = 0; i < ALL_PART; ++i) {

        ++actual_step[i];

        while (step_to_jump[actual_step[i]]) {
          ++actual_step[i];
        }


        if (actual_step[i] > number_of_step[i] - 1) {
          actual_step[i] = 0;
          while (step_to_jump[actual_step[i]]) {
            ++actual_step[i];
          }
        }
      }
      break;

    case 1 : // backward
      for (int i = 0; i < ALL_PART; ++i) {
        --actual_step[i];

        while (step_to_jump[actual_step[i]]) {
          --actual_step[i];
        }


        if (actual_step[i] > 65) {
          actual_step[i] = number_of_step[i] - 1;
          while (step_to_jump[actual_step[i]]) {
            --actual_step[i];
          }
        }
      }
      break;

    case 2 : // ping pong

      byte last_valid_step[ALL_PART];

      for (int i = 0; i < ALL_PART; ++i) {

        if (ping[i]) {
          ++actual_step[i];
          last_valid_step[i] = actual_step[i];

          while (step_to_jump[actual_step[i]]) {
            ++actual_step[i];
            if (actual_step[i] > number_of_step[i] - 1) {
              actual_step[i] = last_valid_step[i] - 2;
              ping[i] = false;
            }
          }

          if (actual_step[i] >= number_of_step[i] - 1) {
            ping[i] = false;
          }

        } else {
          --actual_step[i];
          last_valid_step[i] = actual_step[i];

          while (step_to_jump[actual_step[i]]) {
            --actual_step[i];
            if (actual_step[i] > 65) {
              actual_step[i] = last_valid_step[i] + 2;
              ping[i] = true;
            }
          }

          if (actual_step[i] > 65) {
            ping[i] = true;
          }
        }
      }
      break;

    case 3 :  // random

      for (int i = 0; i < ALL_PART; ++i) {

        byte my_try = random(number_of_step[i]);

        while (step_to_jump[my_try]) {
          my_try = random(number_of_step[i]);
        }
        actual_step[i] = my_try;
      }
      break;

    case 4 : // brownien

      for (int i = 0; i < ALL_PART; ++i) {

        byte proba = random(100);
        byte my_try = random(100);

        if (proba > my_try) {
          ++actual_step[i];

          while (step_to_jump[actual_step[i]]) {
            ++actual_step[i];
          }


          if (actual_step[i] > number_of_step[i] - 1) {
            actual_step[i] = 0;
            while (step_to_jump[actual_step[i]]) {
              ++actual_step[i];
            }
          }
        }
      }
      break;
  }
  step_start = millis();
}