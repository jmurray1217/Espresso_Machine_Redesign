#include <Arduino.h>
#include "stateMachine.h"

void lcdClear();
void lcdPrint(const char* str, int row, int col);
void lcdPrint(int nbr, int row, int col);
void setupLCD();
void updateLCD();
