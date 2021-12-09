#include <Arduino.h>
#include <stdint.h>
#include <SevSeg.h>

#include <Variables.h>
#include <Pinout.h>



SevSeg sevseg;
byte to_print[6];

const char*  general_param[4] {"PAG", "BPn", "DEL", "SnG"};
const char*  mode[2] {"pat","nut"};
const char*  my_string[5] {"frd", "brd", "png", "rnd", "bro"};
const char*  part_param[5] {"nbs", "uAY", "ist", "CLO", "gsi"};
const char*  step_param[3] {"gsi", "rat", "pby"};

void initialize_screen(){

  uint8_t numDigits = 3;
  uint8_t hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, disableDecPoint);
  sevseg.setBrightness(100);
    
}


void update_screen() {
  
  if (which_encoder == 0) {       // General parameter
    sevseg.setChars(general_param[which_parameter/2]);

  } else if (which_encoder == 1){ // Patern
    sevseg.setChars(mode[which_mode]);

  }else if (which_encoder == 2){  // Per part
    sevseg.setChars(part_param[which_part_param/2]);

  }else if (which_encoder == 3){  // Per step
        sevseg.setChars(step_param[which_step_param/2]);

  }else if (which_encoder == 4){  // Data
    
  }
  sevseg.refreshDisplay();

  //Serial.println(which_encoder);
  // 0 = BPM
  // 1 = Clock Divider
  // 2 = Gate length
  // 3 = number of Step
  // 4 = page navigation
  // 5 = Sens de lecture

  //Serial.println(which_way);
  // 0 = Frd forward
  // 1 = Brd Backward
  // 2 = Png Ping Pong
  // 3 = rnd Random
  // 4 = Bro
}