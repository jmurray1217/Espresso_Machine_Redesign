#include "definitions.h"
#include <Arduino.h>

// Beeps a piezo buzzer on BUZZERPIN
 void beep(int time){
  analogWrite(BUZZERPIN, 50);
  delay(time);
  analogWrite(BUZZERPIN, 0);
}