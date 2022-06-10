#include "tempSense.h"

double latestReading = 0.0;

//tempSensor DS1820B init
void setupTempSensor(double *temp)
{


    sensors.begin();
    sensors.requestTemperatures();
    while (!updateTempSensor(temp))
    {
    } // wait until temp sensor updates
}

// Update readings
bool updateTempSensor(double *temperature)
{
    bool result = false;
// call repeatedly in loop, only update after a certain time interval
// returns true if update happened
  if ((millis() - lastTempUpdate) > TEMP_READ_DELAY)
  {
    temperature = sensors.getTempCByIndex(0); // get temp reading in Celcius
    lastTempUpdate = millis();
    sensors.requestTemperatures();
    result = true;
  }
    if (latestReading == -127)
    {                                                // If there is an error with the TC, temperature will be -1
        Serial.println("Thermocouple Probe Error!"); // Temperature is -127 and there is a thermocouple error

        // Prevent run-on heating when thermocouple is disconnected - very important!
        // targetTemp = 0;
        // _turnHeatElementOnOff(false);
        beep(200);
        delay(200);
        beep(200);
        delay(200);
        beep(200);
        delay(20);
        beep(1000);
    }
    return result;
}

// @TODO: Both of these methods are not needed with the MAX6675 implementation,
//        but may be used with different temperature reading chips (namely analog ones)
float getFreshTemp()
{
    return latestReading;
}

float getLastTemp()
{
    return latestReading;
}
