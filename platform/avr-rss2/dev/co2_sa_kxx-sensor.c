#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <i2c.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <avr/eeprom.h>
#include "dev/watchdog.h"
#include "lib/list.h"
#include "lib/memb.h"
#include "co2_sa_kxx-sensor.h"

static int
status(int type)
{
  return 0;
}

static int
configure(int type, int c)
{
  return 0;
}

static int
value(int var)
{
  int val, status;
  uint8_t buf[2], csum;
  int16_t res;

  res = 0;
  i2c_start(I2C_CO2SA_ADDR | I2C_WRITE); 
  if(res)
    goto err;
  
  i2c_write(0x22);
  i2c_write(0x00);

  if(var == CO2_SA_KXX_CO2) {
    i2c_write(0x08);
    i2c_write(0x2A);
  }

  if(var == CO2_SA_KXX_TEMP) {
    i2c_write(0x12);
    i2c_write(0x34);
  }

  if(var == CO2_SA_KXX_RH) {
    i2c_write(0x14);
    i2c_write(0x36);
  }

  i2c_stop();

  if(res)
    goto err;
  
  clock_delay_msec(20);
  
  res = 0;
  i2c_start( I2C_CO2SA_ADDR | I2C_READ);

  if(res)
    goto err;

  status = i2c_readAck();
  buf[0] = i2c_readAck();
  buf[1] = i2c_readAck();
  csum  = i2c_readNak();
  i2c_stop();

  val = ((int16_t) (buf[0]<<8)) | buf[1];

  return val;

 err:
  i2c_stop();
  return 0;
}

SENSORS_SENSOR(co2_sa_kxx_sensor, "CO2", value, configure, status);
