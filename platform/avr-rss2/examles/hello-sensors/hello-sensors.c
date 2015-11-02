/*
 * Copyright (c) 2006, Radio Sensors AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple application showing sensor reading on RSS2 mote
 * \author
 *         Robert Olsson <robert@radio-sensors.com>
 */

#include "contiki.h"

#include <stdio.h>
#include "adc.h"
#include "dev/leds.h"
#include "dev/battery-sensor.h"
#include "dev/temp_mcu-sensor.h"
#include "dev/light-sensor.h"
#ifdef CO2
#include "dev/co2_sa_kxx-sensor.h"
#endif
/*---------------------------------------------------------------------------*/
PROCESS(hello_sensors_process, "Hello sensor process");
AUTOSTART_PROCESSES(&hello_sensors_process);


static int
get_v_mcu(void)
{
  return battery_sensor.value(0);
}
static int
get_t_mcu(void)
{
  return temp_mcu_sensor.value(0);
}
static int
get_light(void)
{
  return light_sensor.value(0);
}
#ifdef CO2
static int
get_co2_sa_kxx(int value)
{
  return co2_sa_kxx_sensor.value(value);
}
#endif

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_sensors_process, ev, data)
{
  PROCESS_BEGIN();

  SENSORS_ACTIVATE(battery_sensor);
  SENSORS_ACTIVATE(temp_mcu_sensor);
  SENSORS_ACTIVATE(light_sensor);
#ifdef CO2
  SENSORS_ACTIVATE(co2_sa_kxx_sensor);
#endif

  leds_init();

  printf("Reading sensors---------\n");

  leds_on(LEDS_RED);
  leds_on(LEDS_YELLOW);

  printf("V_MCU=%-3.1f\n", ((double) get_v_mcu())/1000);
  printf("V_IN=%-4.2f\n", adc_read_v_in());
  printf("V_AD1=%-4.2f\n", adc_read_a1());
  printf("V_AD2=%-4.2f\n", adc_read_a2());
  printf("T_MCU=%-4.1f\n", ((double) get_t_mcu()/10));
  printf("LIGHT=%-d\n", get_light());
#ifdef CO2
  printf("CO2=%-d\n", get_co2_sa_kxx(CO2_SA_KXX_CO2));
#endif

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
