# TFPM01 - The first generation of TF-ATMON Particulate matter sensor

Particulate matter sensor for [TF-ATMON system](https://www.thunderfly.cz/tf-atmon.html) is based on [Sensirion SPS30](https://sensirion.com/products/catalog/SPS30/), [TFGPS01](https://github.com/ThunderFly-aerospace/TFGPS01) and [TFUNIPAYLOAD](https://github.com/ThunderFly-aerospace/TFUNIPAYLOAD01).

Look to the following video for a demonstration flight of a sensor mounted on [TF-G2 autogyro](https://github.com/ThunderFly-aerospace/TF-G2). 

[![Watch the video](https://img.youtube.com/vi/KUhktPDEi8I/hqdefault.jpg) ](https://www.youtube.com/watch?v=KUhktPDEi8I)

The design of TFPM01 is obsolete because the particulate matter sensor is now read out directly by PX4 firmware and therefore is replaced by [TFPM02](https://github.com/ThunderFly-aerospace/TFPM02).

## The Connection diagram between SPS30 and TFUNIPAYLOAD

The sensor is connected to the [TFUNIPAYLOAD](https://github.com/ThunderFly-aerospace/TFUNIPAYLOAD01) by using [SZH-200BK26 wires](https://www.tme.eu/cz/details/szh-200bk26/signalove-konektory-raster-1-50mm/jst/) and [ZHR-5](https://www.tme.eu/cz/details/zhr-5/signalove-konektory-raster-1-50mm/jst/). For testing and development of TFUNIPAYLOAD firmware, the [ATmegaTQ4401A](https://www.mlab.cz/module/ATmegaTQ4401A/) module was used as shown in the diagram.
The ATmega runs the Arduino firmware, which prepares [MAVLink](https://en.wikipedia.org/wiki/MAVLink) messages ready to log and transport to TF-ATMON-enabled GCS. 

The block schematics of design are equivalent to the following photo

![Connection between SPS30 sensor, TFGPS and TFUNIPAYLOAD](doc/img/TFPM01_connection.jpg)
> Do not refer to the photo exactly for pinout. Instead, use the following table

| SPS30 Pin | Signal | MCU | Color |
| ---------------:|:-----:|:-------:|-------|
|   1             | VDD +5V - Supply voltage |  Vcc      | Red   |
|   2             | SDA |  D17 / SDA  + resistor 10k to Vcc   | Black |
|   3             | SCL   |  D16 / SCL + resistor 10k to Vcc     | Black |
|   4             | Interface select  Floating - UART, GND I2C.  |  GND     | Black |
|   5 (outer edge) | GND   |  GND      | Black |

GPS PPS signal is connected to pin 12 (PD4), this [could be changed in source code](https://github.com/ThunderFly-aerospace/TFPM01/blob/13cda4ffa5fd143e18c20526534e9ce3898b00ca/SW/arduino/SPS30MAV_small/SPS30MAV_small.ino#L33).
