COOJA for the avr-rss2 platform
================================
This work updates cooja and avrora to recent MCU platforms with emerging 
support for the Atmel RFR2 radio.

Documentation
-------------
Most of the things are convered in documentation availble so there no
need to duplicate this. Note this is still work in progress

Project home
------------
https://github.com/herjulf/contiki branch wip/avrora-rss2

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
* Fix the avrora 256k MCU problem
* RPC register for R2 radio.
* Update energy class.


Contributors
-------------
Atis Elsts,  Voravit Tanyingyong, Robert Olsson


Git command -- REMOVE
---------------------
git clone https://github.com/herjulf/contiki.git
cd contiki
comment out all text entries in .gitattributes
git reset
git status
git reset --hard
git merge remotes/origin/wip/avrora-rss2
git submodule update --init
contiki/tools/mspsim
ant jar
