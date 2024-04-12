# temp_and_humi_arduino
A Arduino Nano gathers data from a DHT22 modul and displays the data on a 8x8 LED Matrix MAX7219. The power is being delivered through the USB connector.

## Meaning of LEDs on 8x8 matrix
The following table shows what meaning each LED on the matrix has if it is activated. Furthermore the next three chapters explain the meaning of the LEDs in more detail.

| . | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | temp is negativ | temp too high | temp too low | humi too high | humi too low | humi is 0.0% | humi is 100.0% | . |
| 1 | T10 | T20 | T30 | T40 | T50 | T60 | T70 | T80 |
| 2 | T1 | T2 | T3 | T4 | T5 | T6 | T7 | T8 |
| 3 | T0.1 | T0.2 | T0.3 | T0.4 | T0.5 | T0.6 | T0.7 | T0.8 |
| 4 | . | . | . | . | . | . | . | . |
| 5 | H10 | H20 | H30 | H40 | H50 | H60 | H70 | H80 |
| 6 | H1 | H2 | H3 | H4 | H5 | H6 | H7 | H8 |
| 7 | H0.1 | H0.2 | H0.3 | H0.4 | H0.5 | H0.6 | H0.7 | H0.8 |

Explanation of symbols:
- temp/T = Temperature in celsius
- humi/H = Humidity in percent
- . = Placeholder

### First row
The first row (at index 0) contains LEDs for additional information and warnings. Within that row the first LED is activated if the measured temperature is negativ, but if the measured temperature is equal to or greater than 0.0 this LED will be deactivated. The next two LEDs are activated if the measured temperature is too high (temp is above [TEMP_TOO_HIGH](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino)) or too low (temp is lower than [TEMP_TOO_LOW](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino)). The following two LEDs at the two indices 3 and 4 are activated if the measured humidity is too high (humi is above [HUMI_TOO_HIGH](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino)) or too low (temp is lower than [HUMI_TOO_LOW](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino)). The LED at the index 5 is activated if the measured humidity equals 0.0% and the LED at the index 6 is activated if the measured humidity equals 100.0%.

### Second, third and forth row
The three rows at the indices 1, 2 and 3 display the measured temperature. Only the first two numbers before the point and the first number after the point are displayed. The number 9 is displayed in the pattern [PATTERN_TO_DISPLAY_NUMBER_NINE](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino) (On=1, Off=0), because if the binary number 1001 is converted to a decimal number the result is 9.
Some examples for displaying measured temperatures on the 8x8 LED Matrix are:
- temp= 32.45 --> activated LEDs: T10, T20, T30 and T1, T2 and T0.1, T0.2, T0.3, T0.4
- temp= 10.03 --> activated LEDs: T10
- temp= 21.90 --> activated LEDs: T10, T20 and T1 and T0.1, T0.4, T0.5, T0.8
- temp= -05.30 --> activated LEDs: LED at index (0|0) and LED at index (2|0) and T1, T2, T3, T4, T5 and T0.1, T0.2, T0.3

### Fifth row
No LEDs within the fifth row are being activated.

### Sixth, seventh and eighth row
The three rows at the indices 5, 6 and 7 display the measured humidity. Like the display of the temperature, only the first two numbers before the point and the first number after the point are displayed, if the measured humidity is not 100.0%. If the the measured humidity is 100.0% all LEDs within the three rows will be deactivated and the LED at the index (6|0) will be activated. Something similar happens if the measured humidity is 0.0%: all LEDs within the three rows will be deactivated and the LED at the index (5|0) will be activated. The number 9 is displayed in the pattern [PATTERN_TO_DISPLAY_NUMBER_NINE](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino) (On=1, Off=0).
Some examples for displaying measured humidity on the 8x8 LED Matrix are:
- humi= 56.23 --> activated LEDs: H10, H20, H30, H40, H50 and H1, H2, H3, H4, H5, H6 and H0.1, H0.2 
- humi= 49.07 --> activated LEDs: H10, H20, H30, H40 and H1, H4, H5, H8
- humi= 60.84 --> activated LEDs: LED at index (3|0) and H10, H20, H30, H40, H50, H60 and H0.1, H0.2, H0.3, H0.4, H0.5, H0.6, H0.7, H0.8
- humi= 32.10 --> activated LEDs: LED at index (4|0) and H10, H20, H30 and H1, H2 and H0.1


# Structure
The following text shows or/and explains the structure of the hardware and the software of this project.

## Structure of the hardware
The following text and tables show what modules were being used and how to connect them.

### Used hardware
- Arduino Nano
- DHT22
- 8x8 LED Matrix MAX7219
- some single-core cables (jumper wires)

### Connections
Arduino Nano and DHT22:
| Arduino Nano-Pin | DHT22-Pin |
| ----------- | ----------- |
| 3v3 | + |
| D2 | Data |
| GND | - |

Arduino Nano and 8x8 LED Matrix MAX7219:
| Arduino Nano-Pin | 8x8 LED Matrix MAX7219-Pin |
| ----------- | ----------- |
| 5V | VCC |
| GND | GND |
| D11 | DIN |
| D10 | CS |
| D8 | CLK |


## Structure of the software
The following table shows the structure of the [software](https://github.com/RaphWa/temp_and_humi_arduino/blob/main/nano/nano.ino) of the Arduino Nano.

![nano_uml_class_diagram](https://github.com/RaphWa/temp_and_humi_arduino/tree/main/images/nano_uml_class_diagram.svg)
