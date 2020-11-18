#include "ArduinoMavlink.h"
#include <HardwareSerial.h>
#include <sps30.h>
/*

                     Mighty 1284p    
                      +---\/---+
           (D 0) PB0 1|        |40 PA0 (AI 0 / D24)
           (D 1) PB1 2|        |39 PA1 (AI 1 / D25)
      INT2 (D 2) PB2 3|        |38 PA2 (AI 2 / D26)
       PWM (D 3) PB3 4|        |37 PA3 (AI 3 / D27)
    PWM/SS (D 4) PB4 5|        |36 PA4 (AI 4 / D28)
      MOSI (D 5) PB5 6|        |35 PA5 (AI 5 / D29)
  PWM/MISO (D 6) PB6 7|        |34 PA6 (AI 6 / D30)
   PWM/SCK (D 7) PB7 8|        |33 PA7 (AI 7 / D31)
                 RST 9|        |32 AREF
                VCC 10|        |31 GND
                GND 11|        |30 AVCC
              XTAL2 12|        |29 PC7 (D 23)
              XTAL1 13|        |28 PC6 (D 22)
      RX0 (D 8) PD0 14|        |27 PC5 (D 21) TDI
      TX0 (D 9) PD1 15|        |26 PC4 (D 20) TDO
RX1/INT0 (D 10) PD2 16|        |25 PC3 (D 19) TMS
TX1/INT1 (D 11) PD3 17|        |24 PC2 (D 18) TCK
     PWM (D 12) PD4 18|        |23 PC1 (D 17) SDA
     PWM (D 13) PD5 19|        |22 PC0 (D 16) SCL
     PWM (D 14) PD6 20|        |21 PD7 (D 15) PWM
                      +--------+
*/

HardwareSerial &hs = Serial1;
ArduinoMavlink mav(hs);

boolean led_status = false;
uint8_t data[10];

void setup() 
{
  int16_t ret;

  Serial.begin(9600);
  Serial1.begin(57600);

  while(!mav.begin())
  {
    Serial.println("Not Connected!");
    delay(250);
  }

  sensirion_i2c_init();

  while (sps30_probe() != 0) 
  {
    Serial.print("SPS sensor probing failed\n");
    delay(500);
  }
  Serial.print("SPS sensor probing successful\n");

  ret = sps30_start_measurement();
  if (ret < 0) 
  {
    Serial.print("error starting measurement\n");
  }
  Serial.print("measurements started\n");
  
  mav.Stream();
  delay(2000);
}


void loop() 
{
  struct sps30_measurement m;
  char serial[SPS30_MAX_SERIAL_LEN];
  uint16_t data_ready;
  int16_t ret;

  do 
  {
    ret = sps30_read_data_ready(&data_ready);
    if (ret < 0) 
    {
      Serial.print("error reading data-ready flag: ");
      Serial.println(ret);
    } 
    else if (!data_ready)
      Serial.print("data not ready, no new measurement available\n");
    else
      break;
    delay(100); /* retry in 100ms */
  } while (1);

  ret = sps30_read_measurement(&m);
  if (ret < 0) {
    Serial.print("error reading measurement\n");
  } 
  else 
  {
    Serial.print("PM  1.0: ");
    Serial.println(m.mc_1p0);
    Serial.print("PM  2.5: ");
    Serial.println(m.mc_2p5);
    Serial.print("PM  4.0: ");
    Serial.println(m.mc_4p0);
    Serial.print("PM 10.0: ");
    Serial.println(m.mc_10p0);

    uint16_t NC0p5 = round(m.nc_0p5);
    uint16_t NC1p0 = round(m.nc_1p0 - m.nc_0p5);
    uint16_t NC2p5 = round(m.nc_2p5 - m.nc_1p0);
    uint16_t NC4p0 = round(m.nc_4p0 - m.nc_2p5);
    uint16_t NC10p0 = round(m.nc_10p0 - m.nc_4p0);
    
    Serial.print("NC  0.3 - 0.5:  ");
    Serial.println(NC0p5);
    Serial.print("NC  0.5 - 1.0:  ");
    Serial.println(NC1p0);
    Serial.print("NC  1.0 - 2.5:  ");
    Serial.println(NC2p5);
    Serial.print("NC  2.5 - 4.0:  ");
    Serial.println(NC4p0);
    Serial.print("NC  4.0 - 10.0: ");
    Serial.println(NC10p0);

    Serial.print("Typical partical size: ");
    Serial.println(m.typical_particle_size);
    Serial.println();
  
    data[0] = lowByte(NC0p5);
    data[1] = highByte(NC0p5);
    data[2] = lowByte(NC1p0);
    data[3] = highByte(NC1p0);
    data[4] = lowByte(NC2p5);
    data[5] = highByte(NC2p5);
    data[6] = lowByte(NC4p0);
    data[7] = highByte(NC4p0);
    data[8] = lowByte(NC10p0);
    data[9] = highByte(NC10p0);

    // data array (max length 128), data array size, data type (0 default - unknown), target sysid, target compid
    // For unicast (only for logging purposes) set sysid and compid to match the autopilot. For realtime visualisation, you can
    // set sysid and comid to broadcast (0, 0)
    mav.SendTunnelData(data, sizeof(data), 0, 1, 1);
    
    led_status = !led_status;
    digitalWrite(13, led_status);
  }
  delay(1000);
}
