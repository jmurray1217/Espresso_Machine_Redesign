#include "lcd.h"

byte coffeeIcon1[8] = {
  B00000,
  B00000,
  B00000,
  B10001,
  B10001,
  B10001,
  B10001,
  B01110
};

byte coffeeIcon2[8] = {
  B00000,
  B00000,
  B00000,
  B10001,
  B10001,
  B10001,
  B11111,
  B01110
};


byte coffeeIcon3[8] = {
  B00000,
  B00000,
  B00000,
  B10001,
  B10001,
  B11111,
  B11111,
  B01110
};


byte coffeeIcon4[8] = {
  B00000,
  B00000,
  B00000,
  B10001,
  B11111,
  B11111,
  B11111,
  B01110
};

// Would be more efficient with a macro
void lcdClear() {
  #ifdef LCDSF
    sflcd.clear();
  #endif
 
  #ifdef LCDHD
    lcd.clear();
  #endif 
}

// Would be more efficient with a macro
void lcdPrint(const char* str, int row, int col) {
  #ifdef LCDSF
    sflcd.print(str, row, col);
  #endif
 
  #ifdef LCDHD
    lcd.setCursor(col, row);
    lcd.print(str);
  #endif 
}

void lcdPrint(int nbr, int row, int col) {
  #ifdef LCDSF
    sflcd.print(nbr, row, col);
  #endif
 
  #ifdef LCDHD
    lcd.setCursor(col, row);
    lcd.print(nbr);
  #endif
}

void setupLCD() {  
  #ifdef LCDSF
    sflcd.init(); // Setup serial LCD
    sflcd.clear();
  #endif
  
  #ifdef LCDHD
    lcd.begin(16,2);
    lcd.createChar(0,coffeeIcon1);
    lcd.createChar(1,coffeeIcon2);
    lcd.createChar(2,coffeeIcon3);
    lcd.createChar(3,coffeeIcon4);
    lcd.clear();
  #endif
  
  lcdPrint(BANNER,0,0);
  //#ifdef LCDSF
  //  lcd.brightness(DIMVAL); // Dim the LCD
  //#endif
}

// Update the Serial LCD depending on the current state
void updateLCD() {
  boolean modechange = lastbrewmode != brewMode;
  boolean tempchange = lasttemp != getLastTemp();
  boolean rotarychange = lastrotary != rotary.position();  
  switch(brewMode) {
    case BREW_HEAT:
      if(modechange || tempchange) {
        lcdPrint("Brew Heating",0,0);
        lcdPrint("Temp:",1,0);
        lcdPrint("   ",1,6);
        lcdPrint(int(getLastTemp()),1,6);
        lcdPrint("~ ",1,10);
        lcdPrint("   ",1,12);
        lcdPrint(int(targetTemp),1,12);
      }
      break;
    case BREW_READY:
      if(modechange || tempchange) {
        lcdPrint("Ready to brew",0,0);
        lcdPrint("   ",1,0);
        lcdPrint(int(getLastTemp()),1,0);
        lcdPrint("~",1,4);
        lcdPrint("    ",1,6);
        lcdPrint(int(targetTemp),1,6);
      }
      break;
    case STEAM_HEAT:
      if(modechange || tempchange) {
        lcdPrint("Steam Heating",0,0);
        lcdPrint("Temp:",1,0);
        lcdPrint("   ",1,6);
        lcdPrint(int(getLastTemp()),1,6);
        lcdPrint("~ ",1,10);
        lcdPrint("   ",1,12);
        lcdPrint(int(targetTemp),1,12);
      }
      break;
    case STEAM_READY:
      if(modechange || tempchange) {
        lcdPrint("Ready to steam",0,0);
        lcdPrint("   ",1,0);
        lcdPrint(int(getLastTemp()),1,0);
        lcdPrint("~",1,4);
        lcdPrint("   ",1,6);
        lcdPrint(int(targetTemp),1,6);
      }
      break;
    case IDLE:
      if(modechange || tempchange || rotarychange) {
        lcdPrint(BANNER,0,0);
        if(rotary.position() < 5) {
          lcdPrint(" ~brew",1,3);
        }
        else {
          lcdPrint(" ~set ",1,3);
        }
        lcdPrint("   ",1,11); // Get rid of orphaned 3rd digit
        lcdPrint(int(getLastTemp()),1,13);
        lcdPrint("Off",1,0);


      }
      break;
  }
  lastrotary = rotary.position();
  lasttemp = getLastTemp();
  lastbrewmode = brewMode;
}
