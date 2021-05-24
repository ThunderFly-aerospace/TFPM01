# TFPM01 - Particulate matter sensor

Particulate matter sensor is based on [Sensirion SPS30](https://www.tme.eu/cz/details/sps30/snimace-plynu/sensirion/1-101638-10/).

## Connection

The sensor is connected to the MCU ATmega1284P by using [SZH-200BK26 wires](https://www.tme.eu/cz/details/szh-200bk26/signalove-konektory-raster-1-50mm/jst/) and [ZHR-5](https://www.tme.eu/cz/details/zhr-5/signalove-konektory-raster-1-50mm/jst/). For testing the [ATmegaTQ4401A](https://www.mlab.cz/module/ATmegaTQ4401A/) module was used.


![Connection between SPS30 sensor, TFGPS and TFUNIPAYLOAD](doc/img/TFPM01_connection.jpg)
> Do not reffer immage for pinout. 



| SPS30 Pin | Sigal | MCU | Color |
| ---------------:|:-----:|:-------:|-------|
|   1             | VDD +5V - Supply voltage |  Vcc      | Red   |
|   2             | SDA |  D17 / SDA  + resistor 10k to Vcc   | Black |
|   3             | SCL   |  D16 / SCL + resistor 10k to Vcc     | Black |
|   4             | Interface select  Floating - UART, GND I2C.  |  GND     | Black |
|   5 (outer edge) | GND   |  GND      | Black |


GPS PPS signal is connected to pin 12 (PD4), this [could be changed in source code](https://github.com/ThunderFly-aerospace/TFPM01/blob/13cda4ffa5fd143e18c20526534e9ce3898b00ca/SW/arduino/SPS30MAV_small/SPS30MAV_small.ino#L33).
