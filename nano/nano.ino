#include <LedControl.h>

// constants
const double TEMP_TOO_HIGH = 35.00;
const double TEMP_TOO_LOW = 0.00;
const double HUMI_TOO_HIGH = 60.00;
const double HUMI_TOO_LOW = 40.00;

// variables for 8x8 LED Matrix MAX7219
int DIN = 11;
int CS = 10;
int CLK = 8;
LedControl lc=LedControl(DIN, CLK, CS,0);

/**
 * Activates the second LED and deactivates the third LED 
 * in the first row.
 *
 * Meaning: The measured temperature is too high.
 */
void show_too_hot(){
  lc.setLed(0, 0, 1, true);
  lc.setLed(0, 0, 2, false);
}

/**
 * Activates the third LED and deactivates the second LED 
 * in the first row.
 *
 * Meaning: The measured temperature is too low.
 */
void show_too_cold(){
  lc.setLed(0, 0, 2, true);
  lc.setLed(0, 0, 1, false);
}

/**
 * Activates the forth LED and deactivates the fifth LED 
 * in the first row.
 *
 * Meaning: The measured humidity is too high.
 */
void show_too_humid(){
  lc.setLed(0, 0, 3, true);
  lc.setLed(0, 0, 4, false);
}

/**
 * Activates the fifth LED and deactivates the forth LED 
 * in the first row.
 *
 * Meaning: The measured humidity is too low.
 */
void show_not_humid_enough(){
  lc.setLed(0, 0, 4, true);
  lc.setLed(0, 0, 3, false);
}

/**
 * Checks if a temperature or humidity threshold has been reached
 * and lights up LEDs to warn user.
 */
void check_and_show_warnings(double temp, double humi){
  // check temp
  if(temp > TEMP_TOO_HIGH){
    show_too_hot();
  }else if(temp < TEMP_TOO_LOW){
    show_too_cold();
  }

  // check humi
  if(humi > HUMI_TOO_HIGH){
    show_too_humid();
  }else if(humi < HUMI_TOO_LOW){
    show_not_humid_enough();
  }
}

void setup()   {
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
}

void loop() {
  check_and_show_warnings(55.0, 60.0);

  //lc.clearDisplay(0);
  //lc.setRow(0, 0, B10011001);

}