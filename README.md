# temp_and_humi_arduino
A Arduino Nano gathers data from a DHT22 modul and displays the data on a 8x8 LED Matrix MAX7219. The power is being delivered through the USB connector.
The following table shows what meaning each LED on the matrix has if it is activated.

| . | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| 0 | temp is negativ | temp too high | temp too low | humi too high | humi too low | humi is 0.0% | humi is 100.0% | . |
| 1 | T10 | T20 | T30 | T40 | T50 | T60 | T70 | T80 |
| 2 | T1 | T2 | T3 | T4 | T5 | T6 | T7 | T8 |
| 3 | T0.1 | T0.2 | T0.3 | T0.4 | T0.5 | T0.6 | T0.7 | T0.8 |
| 4 | . | . | . | . | . | . | . | . |
| 5 | H10 | H20 | H30 | H40 | H50 | H60 | H70 | H80 |
| 6 | H1 | H2 | H3 | H4 | H5 | H6 | H7 | H8 |
| 7 | H0.1 | H0.2 | H0.3 | H0.4 | H0.5 | H0.6 | H0.7 | H0.8 |

temp/T= Temperature in celsius, humi/H= Humidity in percent, .=no function/meaning


# Structure
The following text shows or/and explains the structure of the hardware and the software of this project.

## Structure of the hardware
The following text and tables show waht modules were being used and how to connect them.

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