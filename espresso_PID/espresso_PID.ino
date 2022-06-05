#include <AutoPID.h>
#include "definitions.h"
#include "stateMachine.h"
#include "tempSense.h"
double temperature, setPoint, outputVal;

// input and output passed by reference, in order to update automagically
AutoPID boilerPID(&temperature, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

enum state brewMode = IDLE;

void setup()
{
  pinMode(WATER_BOILER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  Serial.begin(9600);
  setupTempSensor();

  boilerPID.setBangBang(4);
  boilerPID.setTimeStep(500);

}

void loop()
{
  if (updateTempSensor()){
    temperature = getFreshTemp();
  }
  if ((brewMode == STEAM_HEAT) || (brewMode == STEAM_READY))
    {
      setPoint = 100;
    }
  else if ((brewMode == BREW_HEAT) || (brewMode == BREW_READY))
    {
      setPoint = 95;
    }
  else{
    setPoint = 0;
  }
  boilerPID.run();
  analogWrite(WATER_BOILER_PIN, outputVal);
  digitalWrite(GREEN_LED_PIN, boilerPID.atSetPoint(1)); // Illuminate the Green LED on espresso machine when the boiler is at +-1 degree
}

// Beeps a piezo buzzer on BUZZERPIN
 void beep(int time){
  analogWrite(BUZZERPIN, 50);
  delay(time);
  analogWrite(BUZZERPIN, 0);
}
