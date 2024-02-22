#include <LedControl.h>
#include <math.h>


// constants
const double TEMP_TOO_HIGH = 35.0;
const double TEMP_TOO_LOW = 0.0;
const double HUMI_TOO_HIGH = 60.0;
const double HUMI_TOO_LOW = 40.0;
const byte PATTERN_TO_DISPLAY_NUMBER_NINE = B10111101;

// variables for 8x8 LED Matrix MAX7219
int DIN = 11;
int CS = 10;
int CLK = 8;
LedControl lc=LedControl(DIN, CLK, CS,0);

/**
 * Activates the first LED in the first row if is_temp_negativ is true,
 * otherwise the first LED in the first row will be deactivated.
 *
 * @param is_temp_negativ should be true if measured temp is negativ, otherwise false
 */
void show_if_measured_temp_is_negativ(bool is_temp_negativ){
  if(is_temp_negativ){
    lc.setLed(0, 0, 0, true);
  }else {
    lc.setLed(0, 0, 0, false);
  }
}

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

/**
 * Activates a specified number of LEDs in given row.
 *
 * @param addr address of the display
 * @param row the row of the LEDs (0..7)
 * @param number_of_leds the number of LEDs to activate (0..8)
 */
void activate_specific_number_of_leds_in_a_row(int addr, int row, int number_of_leds){
  lc.setRow(addr, row, B00000000); // clear row

  for(int i=0; i<number_of_leds; i++){
    lc.setLed(addr, row, i, true);
  }
}

/**
 * Shows the measured temperature on the display. 
 * First example: temp == 21.5 --> second row has two activated LEDs, third row has one activated LED, 
 * forth row has five activated LEDs.
 * Second example: temp == 09.8 --> second row has no activated LEDs, 
 * third row has activated LEDs in pattern PATTERN_TO_DISPLAY_NUMBER_NINE, 
 * all LEDs in forth row are activated.
 *
 * @param temp_values_as_char using the first example, on index 0 should be '2', on 1 should be '1' and on 2 should be '5'
 */
void show_temp_on_display(char temp_values_as_char[3]){
  // clear rows of temp
  lc.setRow(0, 1, B00000000);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00000000);

  // calculate values
  int temp_values[3];
  temp_values[0] = temp_values_as_char[0] - '0';
  temp_values[1] = temp_values_as_char[1] - '0';
  temp_values[2] = temp_values_as_char[2] - '0';



  // check if number 9 has to be displayed
  if(temp_values[0] !=9){
    activate_specific_number_of_leds_in_a_row(0, 1, temp_values[0]); // * 10 Celsius
  }else {
    lc.setRow(0, 1, PATTERN_TO_DISPLAY_NUMBER_NINE);
  }
  if(temp_values[1] !=9){
    activate_specific_number_of_leds_in_a_row(0, 2, temp_values[1]); // * 1 Celsius
  }else {
    lc.setRow(0, 2, PATTERN_TO_DISPLAY_NUMBER_NINE);
  }
  if(temp_values[2] !=9){
    activate_specific_number_of_leds_in_a_row(0, 3, temp_values[2]); // * 0.1 Celsius
  }else {
    lc.setRow(0, 3, PATTERN_TO_DISPLAY_NUMBER_NINE);
  }
}

/**
 * Shows the measured temperature on the display.
 * If temp is NaN, nothing on the display will change.
 *
 * @param temp temperature to display
 */
void convert_and_show_temp(double temp){
  if(!isnan(temp)){ // check if temp is NaN
    char buffer[6];
    String(temp).toCharArray(buffer, sizeof(buffer)); // convert double to String and String to char array

    // if temp is negativ
    if(temp<0.0){
      show_if_measured_temp_is_negativ(true);

      if((temp*(-1)) >= 10.00){ // does temp have two digits before the point
        // remove negative sign by pushing first characters one space higher
        buffer[0] = buffer[1]; // 1xyz
        buffer[1] = buffer[2]; // x1yz
        buffer[2] = buffer[3]; // xy.z
        buffer[3] = buffer[4]; // xyz1

        char temp_values[3] = {buffer[0], buffer[1], buffer[3]};
        show_temp_on_display(temp_values);
      }else {
        // remove negative sign by replacing it with a zero
        buffer[0] = '0'; // 0xyz

        char temp_values[3] = {buffer[0], buffer[1], buffer[3]};
        show_temp_on_display(temp_values);
      }

    }else { // if temp is postiv
      show_if_measured_temp_is_negativ(false);

      if(temp >= 10.00){ // does temp have two digits before the point
        char temp_values[3] = {buffer[0], buffer[1], buffer[3]};
        show_temp_on_display(temp_values);
      }else{
        char new_buffer[4];
        new_buffer[0] = '0';
        new_buffer[1] = buffer[0];
        new_buffer[2] = buffer[1];
        new_buffer[3] = buffer[2];

        char temp_values[3] = {new_buffer[0], new_buffer[1], new_buffer[3]};
        show_temp_on_display(temp_values);
      }
    }
  }
  
}

void setup()   {
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);

  // init screen
  lc.setRow(0, 0, B00111100);
  lc.setRow(0, 1, B01000010);
  lc.setRow(0, 2, B10100101);
  lc.setRow(0, 3, B10000001);
  lc.setRow(0, 4, B10100101);
  lc.setRow(0, 5, B10011001);
  lc.setRow(0, 6, B01000010);
  lc.setRow(0, 7, B00111100);

  Serial.begin(9600); // ToDo delete later
}

void loop() {
  // update display after a few seconds
  delay(5000);
  lc.clearDisplay(0);

  // get data
  double temp = 99.9; // ToDo get real data
  double humi = 56.8; // ToDo get real data

  // check for warnings
  check_and_show_warnings(temp, humi);

  // show data
  convert_and_show_temp(temp);
  // ToDo convert_and_show_measured_humi(humi);
}