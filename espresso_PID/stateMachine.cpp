// State machine for modes
#include "stateMachine.h"

enum state setMode(enum state currentMode)
{
  enum state newMode = IDLE;

  // Buttonpress Events
  if (button1Press > 0)
  {

    switch (currentMode)
    {
    // In brew preheat, buttonpress
    case BREW_HEAT:
    {
      saveTemp();
      targetTemp = getSteamTargetTemp();
      #ifdef ENCODER
        rotary.position(targetTemp);
      #endif
      newMode = STEAM_HEAT; // Not preheated, skip brew mode, go to steam preheat
    }
    break;

    // Brew preheated, buttonpress
    case BREW_READY:
    {
      saveTemp();
      targetTemp = getSteamTargetTemp();
      #ifdef ENCODER
        rotary.position(targetTemp);  
      #endif
      newMode = STEAM_HEAT;
    }
    break;

    // In steam preheat, buttonpress
    case STEAM_HEAT:
    {
      saveTemp();
      targetTemp = 0;
      newMode = IDLE; // Not preheated, go to idle
    }
    break;

    // Steam preheated, buttonpress
    case STEAM_READY:
    {
      saveTemp();
      targetTemp = 0;
      newMode = IDLE;
    }
    break;

    case SETTINGS:
    {
      newMode = currentMode;
      if (tmpset == 0)
      {
        rotary.position(getI());
        tmpset++;
      }
      else if (tmpset == 1)
      {
        rotary.position(getD());
        tmpset++;
      }
      else if (tmpset >= 2)
      {
        // exit
        newMode = IDLE;
        tmpset = 0;
      }
    }
    break;

    // In idle mode, buttonpress
    case IDLE:
    {
      newMode = currentMode;
      if (rotary.position() == 0)
      {
        targetTemp = readFloat(ESPRESSO_TEMP_ADDRESS); // from EEPROM. load the saved value
        #ifdef ENCODER
          rotary.position(targetTemp);
        #endif
        // lcd.brightness(BRIGHTVAL);
        newMode = BREW_HEAT; // Go to preheat
        tmpset++;
      }
      else if (rotary.position() >= 1)
      {
        newMode = SETTINGS;
        tmpset = 0;
      }
    }
    break;

    default:
    {
      newMode = currentMode;
    }
    }

    if (newMode == IDLE)
    {
    #ifdef ENCODER
      rotary.position(0); // If this is not set, heating will occur in "off" mode
    #endif
      targetTemp = 0;
      //      lcd.brightness(10); // Dim the LCD
    }

    if (newMode != currentMode)
    {
      if (newMode == SETTINGS)
      {
        rotary.minimum(0);
        rotary.maximum(255);
        rotary.position(getP());
      }
      else if (newMode == IDLE)
      {
        rotary.minimum(0);
        rotary.maximum(9);
        rotary.position(0);
      }
      else if (newMode == BREW_HEAT)
      {
        rotary.minimum(0);
        rotary.maximum(255);
      }
      // click();
      // lcdClear(); // Clear the LCD when switching modes
    }
    button1Press--;
  }

  // Generic (non-button) Events
  else if (currentMode == BREW_HEAT && (getLastTemp() >= targetTemp))
  {
    beep(200);
    delay(100);
    beep(200);
    // lcdClear();
    newMode = BREW_READY; // Preheated
  }
  else if (currentMode == STEAM_HEAT && (getLastTemp() >= targetTemp))
  {
    beep(200);
    delay(100);
    beep(200);
    // lcdClear();
    newMode = STEAM_READY; // Preheated
  }

  else
  {
    newMode = currentMode;
  }

  return newMode;
}
