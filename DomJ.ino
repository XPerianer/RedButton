#include <Keyboard.h>

const int buttonPin = 2;
const char keys[] = {
  // key value or https://www.arduino.cc/en/Reference/KeyboardModifiers
  KEY_LEFT_CTRL,
  KEY_LEFT_ALT,
  'l'
};

const long timing_check_interval = 1000;
long timing_check_left = 0;
bool timing_mode = false;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);
}

void loop() {
  if (timing_mode) {
    
    if (LOW == digitalRead(buttonPin)) {
      Keyboard.press(KEY_RETURN);
    }
    while (LOW == digitalRead(buttonPin))
      ;
      
    Keyboard.releaseAll();
      
    timing_check_left--;
    if(timing_check_left == 0) {
      timing_check_left = timing_check_interval;
      if (Serial.available() > 0) {
        char inChar = Serial.read();
        if (inChar == 'n') {
          timing_mode = false;
          Serial.write("timing ended\n");
        }
      }
    }
  }
  else
  {
    if (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == 't') {
        timing_mode = true;
        timing_check_left = timing_check_interval;
        Serial.write("timing started\n");
      }
    }
    
    if (LOW == digitalRead(buttonPin)) {
      for (int i = 0; i < (sizeof(keys) / sizeof(keys[0])); i++) {
        Keyboard.press(keys[i]);
      }
      while (LOW == digitalRead(buttonPin))
        ;
      
      Keyboard.releaseAll();
    }
  }
 
}
