Getting Started with Contiki for avr-rss2
==========================================
This guide's aim is to help you start using Contiki for RSS2 boards
The platform supports two different RSS2 boards:

* Boards based on the AtMega128RFA1
* Boards based on the AtMega256RFR2

Boards looks the same. "Made in EU" labeled on the AtMega256RFR2 boards
The platform and CPU code, are common for both boards, can be found under 
`$(CONTIKI)/platfrom/avr-rssa The port was developed and tested with RSS2.
This guide assumes that you have basic understanding of how to use the 
command line and perform basic admin tasks on UNIX family OSs.

Boards Features
===============
Chip Antenna. Robust radio performance.
On EUI64 address chip combined with EEPROM
Temp sensor DS18B20, Light Sensor.32 kHz RTC xtal
Comparator. Preprogammed bootloader. 6-pin TTL-USB 
header for FTDI cable for UART.
CE certified by test institute.

UART 
====
The board has one UART via the 6-pin TTL-USB adapter, The recommended
baudrate is 38400 bps. This gives lowest error with respect of the used 
clock frequency.


Port Features
=============
The platform has the following key features:
* Leds



Toolchain needs
===============


Hello-World Example
====================

make TARGET=avr-rss2

Programming using avrdude using serial bootloader. (TTL-USB cable)
Press the RESET button. The bootloader with wait for boot commands 
for 3 seconds.

Commnad line example.

avrdude -p m256rfr2 -c stk500v2 -P /dev/ttyUSB0 -b 38400 -e -U flash:w:hello-world.avr-rss2 

Older boards may use the avr109 boot loader. The stk500v2 uses the yellow
lED while the avr109 uses the red LED.

Seend from the terminal program:

*******Booting Contiki-3.x-1584-g4edfb36*******
I2C: AT24MAC
EUI-64 MAC: fc-c2-3d-0-0-1-82-1c
nullmac sicslowmac, channel 26 , check rate 128 Hz tx power 0
RPL Enabled
Routing Enabled
Hello, world
Online

Addresses [4 max]
fe80::fec2:3d00:1:821c

Neighbors [20 max]

Routes [20 max]


Vendor info
===========
http://radio-sensors.com/
