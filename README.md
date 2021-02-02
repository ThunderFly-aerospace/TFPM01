# TFPM01 - Particulate matter sensor 

Snímač prachových částic je realizován ze senzoru [SPS30](https://www.tme.eu/cz/details/sps30/snimace-plynu/sensirion/1-101638-10/) 

Připojeného k MCU přes [vodiče SZH-200BK26](https://www.tme.eu/cz/details/szh-200bk26/signalove-konektory-raster-1-50mm/jst/) a [dutinky ZHR-5](https://www.tme.eu/cz/details/zhr-5/signalove-konektory-raster-1-50mm/jst/) k modulu [ATmegaTQ4401A](https://www.mlab.cz/module/ATmegaTQ4401A/).


## Connection

| SPS30 Pin | Sigal | MCU | Color |
| ---------------:|:-----:|:-------:|-------|
|   1             | VDD +5V - Supply voltage |  1      | Red   |
|   2             | RX Receiving pin for communication / I2C: Serial data |  2      | Black |
|   3             | SDA   |  3      | Black |
|   4             | Interface select  Floating - UART, GND I2C.  |  4      | Black |
|   5             | GND   |  4      | Black |
