#include <AutoPID.h>

double temperature, setPoint, outputVal;

void setupPID();
void updatePID();
void setBrewTargetTemp(float t) ;

float getBrewTargetTemp();

void setSteamTargetTemp(float t);

float getSteamTargetTemp();