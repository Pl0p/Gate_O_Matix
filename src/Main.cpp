#include <Arduino.h>
#include <stdint.h>

#include <Variables.h>
#include <Pinout.h>
#include <Buttons.h>
#include <Encoder.h>
#include <Screen.h>
#include <led.h>
#include <Sequencer.h>
void read_selector();

void setup() {

  //  Serial.begin(115200);
  pinMode(reset_pin, INPUT);
  void initialize_screen();
  void initialize_LED();
  void initialize_encoders();

    for (int i = 0; i < ALL_PART; ++i) {
      pinMode(gate_out_pin[i], OUTPUT);
    }

    /*Start with pause enable*/
    pause = true;
}

void loop() {

  read_selector();
  handle_buttons_matrix();
  handle_shift_button();
  handle_encoder();
  update_screen();
  update_LEDs();

  reset();

  if (play) {
    if (clock == HIGH) {
      next_step();
      clock = LOW;
    }
  }
}

void read_selector(){

  unsigned long previous_time = 0;
  const float divider = 146.00;


  unsigned long current_time = millis();
  if (current_time - previous_time >= 100UL) { // check for the selector every 100ms
    previous_time = current_time;
    selected_part = round(analogRead(selectorPin) / divider);
  }
}
