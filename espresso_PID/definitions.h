#define ONE_WIRE_BUS 3 //temperature probe signal pin
#define WATER_BOILER_PIN LED_BUILTIN //PIN 13 for now so I can see the output without having to wire anything yet
#define GREEN_LED_PIN 6 //This tells the user that the boiler has reached it desired temperature and it ready to pull the shot

#define TEMP_READ_DELAY 750 //read the temp sensor every ~750ms

//PID Values
#define OUTPUT_MIN 0 //Minimum PWM value that for the boiler 0=NO voltage to the heater
#define OUTPUT_MAX 255 //Maximum PWM value that for the boiler 255=FULL voltage to the heater
#define KP 0
#define KI 5
#define KD 0