#include "stateMachine.h"

// State machine for modes

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
      targetTemp = 95;
      rotary.position(targetTemp);
      newMode = STEAM_HEAT; // Not preheated, skip brew mode, go to steam preheat
    }
    break;

    // Brew preheated, buttonpress
    case BREW_READY:
    {
      saveTemp();
      targetTemp = 100;
      rotary.position(targetTemp);  
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

    // In idle mode, buttonpress
    case IDLE:
    {
      newMode = currentMode;
      if (rotary.position() == 0)
      {
        targetTemp = readFloat(ESPRESSO_TEMP_ADDRESS); // from EEPROM. load the saved value
          rotary.position(targetTemp);
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
      rotary.position(0); // If this is not set, heating will occur in "off" mode
      targetTemp = 0;
      //      lcd.brightness(10); // Dim the LCD
    }

    if (newMode != currentMode)
    {
      if (newMode == IDLE)
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

// Initialize encoder
void setupEncoder(){
  rotary.minimum(0);
  rotary.maximum(255); // Overwritten in individual states
  rotary.position(setPoint);
}

// Update target temp with current rotary position
void updateEncoder() {
  setPoint = rotary.position();
}

// Save current values to respective EEPROM locations
void saveTemp() {
  if((brewMode == BREW_HEAT) || (brewMode == BREW_READY)){
    setBrewTargetTemp(targetTemp);
  }
  else if((brewMode == STEAM_HEAT) || (brewMode == STEAM_READY)){
    setSteamTargetTemp(targetTemp);
  }
}
