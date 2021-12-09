#include <Arduino.h>
#include <stdint.h>

#include <Variables.h>
#include <Pinout.h>

bool general_previousStateCLK;
bool per_part_previousStateCLK;
bool data_previousStateCLK;


void initialize_encoder(){

    pinMode(general_SW_pin, INPUT_PULLUP);
    pinMode(general_led_pin, OUTPUT);
    pinMode (general_inputCLK, INPUT);
    pinMode (general_inputDT, INPUT);
    pinMode(per_part_SW_pin, INPUT_PULLUP);
    pinMode(per_part_led_pin, OUTPUT);
    pinMode (per_part_inputCLK, INPUT);
    pinMode (per_part_inputDT, INPUT);
    pinMode(data_SW_pin, INPUT_PULLUP);
    pinMode(data_led_pin, OUTPUT);
    pinMode (data_inputCLK, INPUT);
    pinMode (data_inputDT, INPUT);
    general_previousStateCLK = digitalRead(general_inputCLK);
    per_part_previousStateCLK = digitalRead(per_part_inputCLK);
    data_previousStateCLK = digitalRead(data_inputCLK);
}

void handle_encoder() {

  unsigned long lastDebounceTime;


//---------------------Encoder 1 General/Patern--------------------------
int count;
bool general_currentStateCLK;
bool general_SW_state;
bool last_general_SW_state = false;
bool general = HIGH;
//---------------------Encoder 2 Per Part/Per Step--------------------------
bool per_part_currentStateCLK;
bool per_part_SW_state;
bool last_per_part_SW_state = false;
bool per_part;
//---------------------Encoder 3 DATA--------------------------
bool data_currentStateCLK;

bool data_SW_state;
bool last_data_SW_state = false;

  //_____________________________________________________
  int reading_general = digitalRead(general_SW_pin);

  if (reading_general != last_general_SW_state) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > 50UL) {

    if (reading_general != general_SW_state) {
      general_SW_state = reading_general;

      if (general_SW_state == HIGH) {
        general = !general;
      }
      if (general) {
        which_encoder = 0; //General parameter
      } else {
        which_encoder = 1; //Patern mode
      }
    }
  }
  last_general_SW_state = reading_general;

  //_____________________________________________________
  int reading_per_part = digitalRead(per_part_SW_pin);

  if (reading_per_part != last_per_part_SW_state) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > 50UL) {

    if (reading_per_part != per_part_SW_state) {
      per_part_SW_state = reading_per_part;

      if (per_part_SW_state == HIGH) {
        per_part = !per_part;
      }
      if (per_part) {
        which_encoder = 2;  // per part parameter
      } else {
        which_encoder = 3;  // per step parameter
      }
    }
  }
  last_per_part_SW_state = reading_per_part;
  //_____________________________________________________
  int reading_data = digitalRead(data_SW_pin);

  if (reading_data != last_data_SW_state) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > 50UL) {

    if (reading_data != data_SW_state) {
      data_SW_state = reading_data;

      if (data_SW_state == HIGH) {

      }
    }
  }
  last_data_SW_state = reading_data;
  //=========================================================================================
  //
  //                                      GENERAL
  //
  //=========================================================================================
  if (general) {                   // Mode = general parameter
    digitalWrite(general_led_pin, LOW);
    general_currentStateCLK = digitalRead(general_inputCLK);

    if (general_currentStateCLK != general_previousStateCLK) {
      which_encoder = 0;
      if (digitalRead(general_inputDT) != general_currentStateCLK) {
        which_parameter--;
      } else {
        which_parameter++;
      }
    }
    general_previousStateCLK = general_currentStateCLK;

    if (which_parameter > 250) {
      which_parameter = 0;
    }
    if (which_parameter > 6) {
      which_parameter = 6;
    }
    //=========================================================================================
    //
    //                                            PATERN
    //
    //=========================================================================================
  } else {                           // Mode = patern
    digitalWrite (general_led_pin, HIGH);
    general_currentStateCLK = digitalRead(general_inputCLK);

    if (general_currentStateCLK != general_previousStateCLK) {
      which_encoder = 1;
      if (digitalRead(general_inputDT) != general_currentStateCLK) {
        which_mode = 0;
      } else {
        which_mode = 1;
      }
    }
    general_previousStateCLK = general_currentStateCLK;
  }
  //=========================================================================================
  //
  //                                      PER PART
  //
  //=========================================================================================
  if (per_part) {                   // Mode = per_part
    digitalWrite(per_part_led_pin, LOW);
    per_part_currentStateCLK = digitalRead(per_part_inputCLK);

    if (per_part_currentStateCLK != per_part_previousStateCLK) {
      which_encoder = 2;
      if (digitalRead(per_part_inputDT) != per_part_currentStateCLK) {
        which_part_param--;
      } else {
        which_part_param++;
      }
    }
    per_part_previousStateCLK = per_part_currentStateCLK;

    if (which_part_param > 250) {
      which_part_param = 0;
    }
    if (which_part_param > 8) {
      which_part_param = 8;
    }
    //=========================================================================================
    //
    //                                      PER STEP
    //
    //=========================================================================================

  } else {                           // Mode per_step
    digitalWrite (per_part_led_pin, HIGH);
    per_part_currentStateCLK = digitalRead(per_part_inputCLK);

    if (per_part_currentStateCLK != per_part_previousStateCLK) {
      which_encoder = 3;
      if (digitalRead(per_part_inputDT) != per_part_currentStateCLK) {
        which_step_param--;
      } else {
        which_step_param++;
      }
    }
    per_part_previousStateCLK = per_part_currentStateCLK;

    if (which_step_param > 250) {
      which_step_param = 0;
    }
    if (which_step_param > 4) {
      which_step_param = 4;
    }
  }

  //=========================================================================================
  //
  //                                      DATA
  //
  //=========================================================================================
  data_currentStateCLK = digitalRead(data_inputCLK);

  if (data_currentStateCLK != data_previousStateCLK) {
    which_encoder = 4;
    if (digitalRead(data_inputDT) != data_currentStateCLK) {
      count --;
    } else {
      count ++;
    }
  }
  data_previousStateCLK = data_currentStateCLK;

}