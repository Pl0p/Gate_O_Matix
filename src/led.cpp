#include <Arduino.h>
#include <stdint.h>

#include <Variables.h>
#include <Pinout.h>


void initialize_LED(){

    pinMode(verrou, OUTPUT);
    pinMode(horloge, OUTPUT);
    pinMode(data, OUTPUT);

    pinMode(verrou2, OUTPUT);
    pinMode(horloge2, OUTPUT);
    pinMode(data2, OUTPUT);
}


void update_LEDs() {

    bool tempo_led[ALL_STEP];

    unsigned long previous = 0;
    unsigned long current = millis();

  for (int i = 0; i < 16; ++i) {
    if (i + page_pos * 16 == actual_step[selected_part]) {
      tempo_led[i] = true;
    } else {
      tempo_led[i] = false;
    }
  }

  if (current - previous >= 100) {
    previous = current;

    for (int i = 0; i < 16; ++i) {
      if (step_to_jump[i + page_pos * 16]) {
        tempo_led[i] = !tempo_led[i];
      }
    }
  }

  digitalWrite(verrou, LOW);
  digitalWrite(verrou2, LOW);

  for (int i = 16; i >= 0; --i) {
    digitalWrite(horloge, LOW);
    digitalWrite(horloge2, LOW);
    digitalWrite(data, tempo_led[i]);
    digitalWrite(data2, step_state[selected_part][i + page_pos * 16]);
    digitalWrite(horloge, HIGH);
    digitalWrite(horloge2, HIGH);
  }
  digitalWrite(verrou, HIGH);
  digitalWrite(verrou2, HIGH);
}