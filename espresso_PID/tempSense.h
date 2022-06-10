#include <OneWire.h>
#include <DallasTemperature.h>
#include "definitions.h"
#include "buzzer.h"

void setupTempSensor(double *temp);
bool updateTempSensor(double *temperature);
float getFreshTemp();
float getLastTemp();

unsigned long lastTempUpdate; // tracks clock time of last temp update
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);    
    