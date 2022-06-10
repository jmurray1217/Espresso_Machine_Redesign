#define ONE_WIRE_BUS 3               // temperature probe signal pin
#define WATER_BOILER_PIN LED_BUILTIN // PIN 13 for now so I can see the output without having to wire anything yet
#define GREEN_LED_PIN 6              // This tells the user that the boiler has reached it desired temperature and it ready to pull the shot

#define TEMP_READ_DELAY 750 // read the temp sensor every ~750ms

// PID Values
#define OUTPUT_MIN 0   // Minimum PWM value that for the boiler 0=NO voltage to the heater
#define OUTPUT_MAX 255 // Maximum PWM value that for the boiler 255=FULL voltage to the heater
#define KP 0
#define KI 5
#define KD 0

#define BUZZERPIN 10 // Buzzer pin
#define SSRPIN 5     // This is a pin number on PORTD (e.g., PD5)

// **** Encoder Options ****
#define ENCODERPINA 2 // Pins for rotary encoder
#define ENCODERPINB 3 // Must be interrupt-capable pins
#define DUMMYBUTTON 9

// **** SparkFun Serial LCD options ****
#define LCDROWS 2    // How many rows your LCD has
#define LCDCOLS 16   // How many colums your LCD has
#define DIMVAL 10    // Idle LCD brightness (%)
#define BRIGHTVAL 80 // In use LCD brightness (%)

// **** Serial Interface Options ****
#ifdef SERIAL
#define AUTO_PRINT_INTERVAL 200 // milliseconds
#define MAX_DELTA 100
#define MIN_DELTA 0.01
#define PRINT_PLACES_AFTER_DECIMAL 2 // set to match MIN_DELTA
#endif

// ***** ETC *****
#define PID_UPDATE_INTERVAL 440 // Interval to update PID (ms)

#define BANNER "The Caffeinator 2.0" // Displayed on LCD when idle, and serial interface
