#include <Arduino.h>
#define HASLED

#define FET_PIN 5 //14 //Define FET pin to simulate fan speed
#define FAN_SENSE_PIN 4 //14 //Define pin on which to sense the fan speed

#define CONST_TIME 4 //125hz = 4ms for on and 4ms for off
#define CONST_TIME_CHECK_FAN 1250 //Check only every 1250/125hz=10 seconds if fan is still running.

#ifdef HASLED
  #define LED_PIN 13 //2 //Define blinking LED pin
#endif

unsigned long pulseHigh; // Integer variable to capture High time of the incoming pulse
unsigned long pulseLow; // Integer variable to capture Low time of the incoming pulse
float pulseTotal; // Float variable to capture Total time of the incoming pulse
float frequency; // Calculated Frequency
bool FanOK=true; // Used to signal Fan troubles 

int Countdown = 0;  

void setup() {
  // put your setup code here, to run once:
  pinMode(FET_PIN, OUTPUT); // Initialize the FET pin as an output
  pinMode(FAN_SENSE_PIN, INPUT_PULLUP); // Initialize the FAN_SENSE pin as an input with a pullup
  #ifdef HASLED
    pinMode(LED_PIN, OUTPUT); // Initialize the FET pin as an output
    digitalWrite(LED_PIN, LOW); // Turn the LED OFF
  #endif
}

void loop() {
  //We check if the fan is turning, but we only check if it was in a failed state or if a period like 10 seconds passed 
  //   otherwise it interferes too much with the output pulse.
  if (Countdown <= 0 || FanOK == false) {
    pulseHigh = pulseIn(FAN_SENSE_PIN,HIGH, 200000);
    pulseLow = pulseIn(FAN_SENSE_PIN,LOW, 200000);
    if (pulseHigh == 0) pulseHigh = 60000000;
    if (pulseLow == 0) pulseLow = 60000000;

    pulseTotal = pulseHigh + pulseLow; // Time period of the pulse in microseconds
    frequency=1000000/pulseTotal; // Frequency in Hertz (Hz)

    if (frequency >= 30) {
      FanOK = true;
    } else {
      FanOK = false;
    }
    Countdown = CONST_TIME_CHECK_FAN;
  } else {
    Countdown--;
  }
  
  if (FanOK) {
    #ifdef HASLED
      digitalWrite(LED_PIN, HIGH); // Turn the LED on
    #endif
    digitalWrite(FET_PIN, LOW); // Turn the FET on (Note that LOW is the voltage level)
    delay(CONST_TIME); 
    digitalWrite(FET_PIN, HIGH); // Turn the FET off by making the voltage HIGH
    delay(CONST_TIME);
  } else {
    #ifdef HASLED
      digitalWrite(LED_PIN, LOW); // Turn the LED off
    #endif
  }
}

