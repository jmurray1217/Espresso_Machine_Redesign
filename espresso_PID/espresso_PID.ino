#include "pid.h"
#include "definitions.h"
#include "stateMachine.h"
#include "tempSense.h"

extern enum state brewMode = IDLE;

void setup()
{
  pinMode(WATER_BOILER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  Serial.begin(9600);
  setupTempSensor(&temperature);

}

void loop()
{
  updateTempSensor(&temperature);
  updatePID();
  analogWrite(WATER_BOILER_PIN, outputVal);
  digitalWrite(GREEN_LED_PIN, boilerPID.atSetPoint(1)); // Illuminate the Green LED on espresso machine when the boiler is at +-1 degree
}


