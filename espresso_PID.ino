/*

*/
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
    pinMode(3, INPUT);
    pinMode(6, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  Serial.print(" - Fehrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(6, LOW);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(6, HIGH);
  delay(250);
}
