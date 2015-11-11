Sniffer application host side
=============================
This a a Unix application to link between the serial port having the
sensor node connected and Wireshark or tcpdump. It is a modified wsbridge 
(See copyright i file) code to use the format used by sensniff. 
See the: 
https://github.com/g-oikonomou/sensniff.

Function
--------
The mote captures WSN data and formats according sensniff format sends
over the serial line. The data is binary. The wsbridge reads reads serial 
line (typically /dev/ttyUSB) on Linux systems decodes the sensnaiff and 
create timestamp and adds the the PCAP farming and writes the result to 
a FIFO or named pipe. /tmp/wireshark.

Bulld
-----
Just use the Makefile. Put binary for convince in your path.

Usage
-----
* wsbridge /dev/ttYUSB
* wireshart -k -i /tmp/wireshark

Default serial port speed
-------------------------
38400 bps

