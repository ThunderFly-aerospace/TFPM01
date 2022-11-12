# TFPM01 - TF-ATMON Particulate matter sensor

Particulate matter sensor for [TF-ATMON system](https://www.thunderfly.cz/tf-atmon.html) is based on [Sensirion SPS30](https://sensirion.com/products/catalog/SPS30/).

## Connection

The sensor is connected to the MCU ATmega1284P by using [SZH-200BK26 wires](https://www.tme.eu/cz/details/szh-200bk26/signalove-konektory-raster-1-50mm/jst/) and [ZHR-5](https://www.tme.eu/cz/details/zhr-5/signalove-konektory-raster-1-50mm/jst/). For testing the [ATmegaTQ4401A](https://www.mlab.cz/module/ATmegaTQ4401A/) module was used.
The ATmega runs the Arduino firmware, which prepare [MAVLink](https://en.wikipedia.org/wiki/MAVLink) messages ready to logging and transport to TF-ATMON enabled GCS. 

Block schematic of that connection reflect following photo:

![Connection between SPS30 sensor, TFGPS and TFUNIPAYLOAD](doc/img/TFPM01_connection.jpg)
> Do not reffer image for pinout. 


| SPS30 Pin | Sigal | MCU | Color |
| ---------------:|:-----:|:-------:|-------|
|   1             | VDD +5V - Supply voltage |  Vcc      | Red   |
|   2             | SDA |  D17 / SDA  + resistor 10k to Vcc   | Black |
|   3             | SCL   |  D16 / SCL + resistor 10k to Vcc     | Black |
|   4             | Interface select  Floating - UART, GND I2C.  |  GND     | Black |
|   5 (outer edge) | GND   |  GND      | Black |


GPS PPS signal is connected to pin 12 (PD4), this [could be changed in source code](https://github.com/ThunderFly-aerospace/TFPM01/blob/13cda4ffa5fd143e18c20526534e9ce3898b00ca/SW/arduino/SPS30MAV_small/SPS30MAV_small.ino#L33).
