# temp_and_humi_arduino
A Arduino Nano gathers data from a DHT22 modul and displays the data on a 8x8 LED Matrix MAX7219. The power is being delivered through the USB connector.

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