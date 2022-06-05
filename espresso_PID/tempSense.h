#include <OneWire.h>
#include <DallasTemperature.h>

void setupTempSensor();
bool updateTempSensor();
float getFreshTemp();
float getLastTemp();

unsigned long lastTempUpdate; // tracks clock time of last temp update
OneWire oneWire;
DallasTemperature sensors;
