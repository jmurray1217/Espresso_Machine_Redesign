#include "pid.h"

void setupPID(){
    

// input and output passed by reference, in order to update automagically
    AutoPID boilerPID(&temperature, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
    boilerPID.setBangBang(4);
    boilerPID.setTimeStep(500);
}

void updatePID() {
  boilerPID.run();
}

float t_brew,t_steam;

void setBrewTargetTemp(float t) {
  t_brew = t;
//  writeFloat(t, ESPRESSO_TEMP_ADDRESS);
}

float getBrewTargetTemp() {
  return t_brew;
//  return readFloat(ESPRESSO_TEMP_ADDRESS);
}

void setSteamTargetTemp(float t) {
  t_steam = t;
}

float getSteamTargetTemp() {
  return t_steam;
}
