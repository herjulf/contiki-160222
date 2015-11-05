Getting Started with Contiki using avr-rss2
===========================================
This guide's aim is to help you start using Contiki for RSS2 boards
The platform supports two different RSS2 boards:

* Based on MCU AtMega256RFR2
* Based on MCU AtMega128RFA1 (bonus) 

Boards looks the same. "Made in EU" labeled on the AtMega256RFR2 boards
The platform and CPU code, are common for both boards, can be found under 
`$(CONTIKI)/platfrom/avr-rssa. The port was developed and tested with RSS2.
This guide assumes that you have basic understanding of how to use the 
command line and perform basic admin tasks on UNIX family OSs. You should'
also have understanding about the Contiki OS design as well have C 
programming skills.

Boards Features
----------------
Chip Antenna. Robust radio performance.
Unique EUI64 address via chip combined with EEPROM
Temp sensor DS18B20, Light Sensor.32 kHz RTC xtal
Comparator chip and input. Preprogammed bootloader. 
6-pin TTL-USB header for FTDI cable for UART. P-FET 
(relay) for power on/off of sensors.
CE certified by test institute.

UART 
----
The board has one UART via the 6-pin TTL-USB adapter, The recommended
baudrate is 38400 bps. This speed gives the lowest error with respect 
of the used clock frequency used internally.

Port Features
--------------
The platform has the following key features:
* Standard, E64 address from built-in chip.
* First hooks for RPC (Reduced Power Consumption) for AtMegaXXXRFR2. 

Toolchain needs
---------------
The Atmel toolcahin is available in most operating system. 
Note. The native OS packages does not yet support the new 
AtMega256RfR2 MCU.

We'll use toolchain from Atmels web-site. You might also consider 
Instant Contiki


* For Linux.
See http://www.atmel.com/tools/ATMELAVRTOOLCHAINFORLINUX.aspx
Download the proper 8-bit platform 32 or 64 bit.
Unpack unpack under /usr/local

Also add to your search PATH. For example .bashrc add:
export PATH=$PATH:/usr/local/avr8-gnu-toolchain-linux_x86/bin

* For Windows.
Goes here

Contiki build TARGET
--------------------
make TARGET=avr-rss2

For AtMega128RFA1 boards:
make TARGET=avr-rss2 MCU=atmega128rfa1  BOOTLOADER_START=0x1F800

Flashing
--------
Programming using avrdude using serial bootloader. (TTL-USB cable)
Press the RESET button. The bootloader with wait for boot commands 
for 3 seconds.

Flashing commnad line example:
avrdude -p m256rfr2 -c stk500v2 -P /dev/ttyUSB0 -b 38400 -e -U flash:w:hello-world.avr-rss2 

Older boards may use the avr109 boot loader. The stk500v2 uses the yellow 
lED while the avr109 uses the red LED.

Tested applications and examples
---------------------------------
hello-world
ipv6/rpl-udp
ipv6/simple-udp-rpl
rime
ipv6/multicast
example-shell  Needs symbol.c to be added to project also seems like
in core/dev/serial-line.c process_poll must be replaced with 
process_post.

  /* Wake up consumer process */
-  process_poll(&serial_line_process);
+  process_post(&serial_line_process, 0, 0);


Platform tutorial applications
.-----------------------------
Example to read out various sensors leds serial numbers etc.
platform/avr-rss2/examples/hello-sensors/

This example shows the sensd data encoding. But UDP using 6lowpan.
platform/avr-rss2/examles/ipv6/rpl-udp-report/


Approvals
---------
Summary: R&TTE 73/23/EEC, 89/336/EEC and 99/5/EC
Safety: EN 60950-1:2006 + A12: 2011
RF: ETSI EN 300 328 V1.7.1 (2006-10)
EMC: ETSI EN 301 489-1 V1.9.2 (2011-09), ETSI EN 301 489-17 V2.2.1 (2012-09)
EMF: EN 62479:2010
Human exposure to electromagnetic fields: EN 62479:2010 

Commercial availability
------------------------
Through vendor and though resellers. Note board is will only available 
were CE approval is covered. This may be further restricted by WEEE.
Contact vendor. For research legislation is more relaxed in most 
countries.

References
----------
AtMega256RFR2 chip documentaion. Available via Atmel.
Schematics and boards description. Available via Radio-Senors
Smart Reduced Power Consumption Techniques. AT02594. Available via Atmel.

ToDo
-----
Shell and UART input.
API for radio power saving settings introduced Atmels app note AT02594. 
Also function for the desensitizing RPC resister.

Vendor info
-----------
http://radio-sensors.com/

Maintainer
----------
Robert Olsson <robert@radio-sensors.com>
