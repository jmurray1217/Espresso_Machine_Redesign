#include <AutoPID.h>
#include <OneWire.h>
#include <DallasTemperature.h>

double temperature, setPoint, outputVal;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//input and output passed by reference, in order to update automagically
AutoPID boilerPID(&temperature, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

unsigned long lastTempUpdate; //tracks clock time of last temp update

//call repeatedly in loop, only update after a certain time interval
//returns true if update happened
bool updateBoilerTemp() {
  if ((millis() - lastTempUpdate) > TEMP_READ_DELAY){
    temperature = sensors.getTempCByIndex(0); //get temp reading in Celcius
    lastTempUpdate = millis();
    sensors.requestTemperatures();
    return true;
  }
  return false;
}

void setup() {
    pinMode(WATER_BOILER_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    Serial.begin(9600);
    sensors.begin();
    sensors.requestTemperatures();
    while (!updateBoilerTemp()){} //wait until temp sensor updates

    boilerPID.setBangBang(4);
    boilerPID.setTimeStep(500);

}

void loop() {
  updateBoilerTemp();
  setPoint = 95;
  boilerPID.run();
  analogWrite(WATER_BOILER_PIN, outputVal);
  digitalWrite(GREEN_LED_PIN, boilerPID.atSetPoint(1)); //Illuminate the Green LED on espresso machine when the boiler is at +-1 degree
}
