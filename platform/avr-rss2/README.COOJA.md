COOJA for avr-rss2 platform
============================
This work updates cooja and avrora to recent MCU platforms with emerging 
support for the Atmel RFR2 radio.

Documentation
-------------
Most of the thinga are convered in documentation availble so there no
need to duplicate this. Note this is still work in progress

Project home
------------
https://github.com/herjulf/contiki branch wip/avrora-

Installation
------------
You need to setup you java environment and install needed components. 
For mspsim. For mspsim:

https://github.com/contiki-os/contiki/wiki/MSP430X

Examples
---------
Platform specific examples:
* examples/hello-world/rss2-hello-world.csc
* platform/avr-rss2/examples/ipv6/rpl-udp-report/rss2-rpl-udp.csc

Known issues:
------------
* MCU=atmega256rfr2 does not yet work. MCU=atmega128rfr2 with Cooja as
  a workaround. Probably some problem parsing elf on MCU's > 128k?

* Timeline plugin uses all all memory and crashes simulation.

TODO
----
* RPC register for R2 radio.
* Fix 

Contributors
-------------
Atis Elsts,  Voravit Tanyingyong, Robert Olsson
