#include <Arduino.h>
#include "pid.h"
#include "encoder.h"
#include "buzzer.h"
#include "Quadrature.h"
#include "definitions.h"
#include "tempSense.h"

Quadrature rotary(ENCODERPINA, ENCODERPINB);

void setupEncoder();
void updateEncoder();
void saveTemp();

enum state
{
    IDLE,
    BREW_HEAT,
    BREW_READY,
    STEAM_HEAT,
    STEAM_READY,
    SETTINGS
};

int button1Press = 0;