/*
 * Copyright (c) 2006, Technical University of Munich
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
 * @(#)$$
 */

/**
 * \file
 *         Configuration for Atmel ATmega128rfa1
 * \author
 *         David Kopf <dak664@embarqmail.com>
 */

#ifndef CONTIKI_CONF_H_
#define CONTIKI_CONF_H_

/* Platform name, type, and MCU clock rate */
#define PLATFORM_NAME  "RFA1"
#define PLATFORM_TYPE  ATMEGA128RFA1
#ifndef F_CPU
#define F_CPU          8000000UL
#endif

#include <stdint.h>

/* The AVR tick interrupt usually is done with an 8 bit counter around 128 Hz.
 * 125 Hz needs slightly more overhead during the interrupt, as does a 32 bit
 * clock_time_t.
 */
 /* Clock ticks per second */
#define CLOCK_CONF_SECOND 128

typedef uint32_t clock_time_t;
#define CLOCK_LT(a,b)  ((int32_t)((a)-(b)) < 0)

/* These routines are not part of the contiki core but can be enabled in cpu/avr/clock.c */
void clock_delay_msec(uint16_t howlong);
void clock_adjust_ticks(clock_time_t howmany);

/* Michael Hartman's atmega128rfa1 board has an external 32768Hz crystal connected to TOSC1 and 2 pins similar to the Raven 1284p */
/* and theoretically can use TIMER2 with it to keep time. Else TIMER0 is used. */
/* The sleep timer requires the crystal and adds a TIMER2 interrupt routine if not already define by clock.c */
#define AVR_CONF_USE32KCRYSTAL 0

/* Michael Hartman's protobyte board has LED on PORTE1, used for radio on indication */
/* However this results in disabling UART0. */
#define RF230BB_CONF_LEDONPORTE1  0

/* COM port to be used for SLIP connection. This is usually UART0, but see above */
#if RF230BB_CONF_LEDONPORTE1
#define SLIP_PORT RS232_PORT_1
#else
#define SLIP_PORT RS232_PORT_0
#endif

/* Pre-allocated memory for loadable modules heap space (in bytes)*/
/* Default is 4096. Currently used only when elfloader is present. Not tested on Raven */
//#define MMEM_CONF_SIZE 256

/* Starting address for code received via the codeprop facility. Not tested. */
typedef unsigned long off_t;
//#define EEPROMFS_ADDR_CODEPROP 0x8000

/* Logging adds 200 bytes to program size. RS232 output slows down webserver. */
//#define LOG_CONF_ENABLED         1

/* RADIOSTATS is used in rf230bb, clock.c and the webserver cgi to report radio usage */
/* It has less overhead than ENERGEST */
#define RADIOSTATS                1

/* More extensive stats, via main loop printfs or webserver status pages */
#define ENERGEST_CONF_ON          1

/* Packet statistics */
typedef unsigned short uip_stats_t;
#define UIP_STATISTICS            0

/* Available watchdog timeouts depend on mcu. Default is WDTO_2S. -1 Disables the watchdog. */
/* AVR Studio simulator tends to reboot due to clocking the WD 8 times too fast */
//#define WATCHDOG_CONF_TIMEOUT -1

/* Debugflow macro, useful for tracing path through mac and radio interrupts */
//#define DEBUGFLOWSIZE 128


/* Define MAX_*X_POWER to reduce tx power and ignore weak rx packets for testing a miniature multihop network.
 * Leave undefined for full power and sensitivity.
 * tx=0 (3dbm, default) to 15 (-17.2dbm)
 * RF230_CONF_AUTOACK sets the extended mode using the energy-detect register with rx=0 (-91dBm) to 84 (-7dBm)
 *   else the rssi register is used having range 0 (91dBm) to 28 (-10dBm)
 *   For simplicity RF230_MIN_RX_POWER is based on the energy-detect value and divided by 3 when autoack is not set.
 * On the RF230 a reduced rx power threshold will not prevent autoack if enabled and requested.
 * These numbers applied to both Raven and Jackdaw give a maximum communication distance of about 15 cm
 * and a 10 meter range to a full-sensitivity RF230 sniffer.
#define RF230_MAX_TX_POWER 15
#define RF230_MIN_RX_POWER 30
 */
  /* The rf231 and atmega128rfa1 can use an rssi threshold for triggering rx_busy that saves 0.5ma in rx mode */
/* 1 - 15 maps into -90 to -48 dBm; the register is written with RF230_MIN_RX_POWER/6 + 1. Undefine for -100dBm sensitivity */
//#define RF230_MIN_RX_POWER        0

/* Network setup */
/* TX routine passes the cca/ack result in the return parameter */
#define RDC_CONF_HARDWARE_ACK    1
/* TX routine does automatic cca and optional backoffs */
#define RDC_CONF_HARDWARE_CSMA   1
/* Allow MCU sleeping between channel checks */
#define RDC_CONF_MCU_SLEEP         1

#if NETSTACK_CONF_WITH_IPV6
#define LINKADDR_CONF_SIZE        8
#define UIP_CONF_ICMP6            1
#define UIP_CONF_UDP              1
#define UIP_CONF_TCP              1
#define NETSTACK_CONF_NETWORK     sicslowpan_driver
#define SICSLOWPAN_CONF_COMPRESSION SICSLOWPAN_COMPRESSION_HC06
#else
/* ip4 should build but is largely untested */
#define LINKADDR_CONF_SIZE        2
#define NETSTACK_CONF_NETWORK     rime_driver
#endif

#define UIP_CONF_LL_802154        1
#define UIP_CONF_LLH_LEN          0

/* 10 bytes per stateful address context - see sicslowpan.c */
/* Default is 1 context with prefix aaaa::/64 */
/* These must agree with all the other nodes or there will be a failure to communicate! */
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS 1
#define SICSLOWPAN_CONF_ADDR_CONTEXT_0 {addr_contexts[0].prefix[0]=0xaa;addr_contexts[0].prefix[1]=0xaa;}
#define SICSLOWPAN_CONF_ADDR_CONTEXT_1 {addr_contexts[1].prefix[0]=0xbb;addr_contexts[1].prefix[1]=0xbb;}
#define SICSLOWPAN_CONF_ADDR_CONTEXT_2 {addr_contexts[2].prefix[0]=0x20;addr_contexts[2].prefix[1]=0x01;addr_contexts[2].prefix[2]=0x49;addr_contexts[2].prefix[3]=0x78,addr_contexts[2].prefix[4]=0x1d;addr_contexts[2].prefix[5]=0xb1;}

/* Take the default TCP maximum segment size for efficiency and simpler wireshark captures */
/* Use this to prevent 6LowPAN fragmentation (whether or not fragmentation is enabled) */
//#define UIP_CONF_TCP_MSS       48

#define UIP_CONF_IP_FORWARD      0
#define UIP_CONF_FWCACHE_SIZE    0

#define UIP_CONF_IPV6_CHECKS     1
#define UIP_CONF_IPV6_QUEUE_PKT  1
#define UIP_CONF_IPV6_REASSEMBLY 0

#define UIP_CONF_UDP_CHECKSUMS   1
#define UIP_CONF_TCP_SPLIT       1
#define UIP_CONF_DHCP_LIGHT      1


#if 1 /* No radio cycling */

#define NETSTACK_CONF_NETWORK rime_driver
#define NETSTACK_CONF_MAC     csma_driver
#define NETSTACK_CONF_RDC     contikimac_driver
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8
#define NETSTACK_CONF_FRAMER  contikimac_framer

#define NETSTACK_CONF_RADIO       rf230_driver
#define CHANNEL_802_15_4          26
/* AUTOACK receive mode gives better rssi measurements, even if ACK is never requested */
#define RF230_CONF_AUTOACK        1
/* 1 + Number of auto retry attempts 0-15 (0 implies don't use extended TX_ARET_ON mode) */
#define RF230_CONF_FRAME_RETRIES    2
/* Number of csma retry attempts 0-5 in extended tx mode (7 does immediate tx with no csma) */
#define RF230_CONF_CSMA_RETRIES   5
/* Default is one RAM buffer for received packets. More than one may benefit multiple TCP connections or ports */
#define RF230_CONF_RX_BUFFERS     3
#define SICSLOWPAN_CONF_FRAG      1
/* Most browsers reissue GETs after 3 seconds which stops fragment reassembly so a longer MAXAGE does no good */
#define SICSLOWPAN_CONF_MAXAGE    3
/* How long to wait before terminating an idle TCP connection. Smaller to allow faster sleep. Default is 120 seconds */
/* If wait is too short the connection can be reset as a result of multiple fragment reassembly timeouts */
#define UIP_CONF_WAIT_TIMEOUT    20
/* 211 bytes per queue buffer */
#define QUEUEBUF_CONF_NUM         8
/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2
/* Allocate remaining RAM as desired */
/* 30 bytes per TCP connection */
/* 6LoWPAN does not do well with concurrent TCP streams, as new browser GETs collide with packets coming */
/* from previous GETs, causing decreased throughput, retransmissions, and timeouts. Increase to study this. */
/* ACKs to other ports become interleaved with computation-intensive GETs, so ACKs are particularly missed. */
/* Increasing the number of packet receive buffers in RAM helps to keep ACKs from being lost */
#define UIP_CONF_MAX_CONNECTIONS  4
/* 2 bytes per TCP listening port */
#define UIP_CONF_MAX_LISTENPORTS  4
/* 25 bytes per UDP connection */
#define UIP_CONF_UDP_CONNS       10
/* See uip-ds6.h */
#define NBR_TABLE_CONF_MAX_NEIGHBORS      20
#define UIP_CONF_DS6_DEFRT_NBU    2
#define UIP_CONF_DS6_PREFIX_NBU   3
#define UIP_CONF_MAX_ROUTES    20
#define UIP_CONF_DS6_ADDR_NBU     3
#define UIP_CONF_DS6_MADDR_NBU    0
#define UIP_CONF_DS6_AADDR_NBU    0


#elif 1  /* Contiki-mac radio cycling */
//#define NETSTACK_CONF_MAC         nullmac_driver
/* csma needed for burst mode at present. Webserver won't work without it */
#define NETSTACK_CONF_MAC         csma_driver
#define NETSTACK_CONF_RDC         contikimac_driver
/* Default is two CCA separated by 500 usec */
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE   8
/* So without the header this needed for RPL mesh to form */
#define CONTIKIMAC_FRAMER_CONF_SHORTEST_PACKET_SIZE   43-18  //multicast RPL DIS length
/* Not tested much yet */
#define WITH_PHASE_OPTIMIZATION                0
#define CONTIKIMAC_CONF_COMPOWER               1
#define RIMESTATS_CONF_ENABLED                 1

#if NETSTACK_CONF_WITH_IPV6
#define NETSTACK_CONF_FRAMER      framer802154
#else /* NETSTACK_CONF_WITH_IPV6 */
#define NETSTACK_CONF_FRAMER      contikimac_framer
#endif /* NETSTACK_CONF_WITH_IPV6 */

#define NETSTACK_CONF_RADIO       rf230_driver
#define CHANNEL_802_15_4          26
/* The radio needs to interrupt during an rtimer interrupt */
#define RTIMER_CONF_NESTED_INTERRUPTS 1
#define RF230_CONF_AUTOACK        1
/* A 0 here means non-extended mode; 1 means extended mode with no retry, >1 for retrys */
/* Contikimac strobes on its own, but hardware retries are faster */
#define RF230_CONF_FRAME_RETRIES  1
/* Long csma backoffs will compromise radio cycling; set to 0 for 1 csma */
#define RF230_CONF_CSMA_RETRIES   0
#define SICSLOWPAN_CONF_FRAG      1
#define SICSLOWPAN_CONF_MAXAGE    3
/* 211 bytes per queue buffer. Contikimac burst mode needs 15 for a 1280 byte MTU */
#define QUEUEBUF_CONF_NUM         15
/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2
/* Allocate remaining RAM. Not much left due to queuebuf increase  */
#define UIP_CONF_MAX_CONNECTIONS  2
#define UIP_CONF_MAX_LISTENPORTS  4
#define UIP_CONF_UDP_CONNS        5
#define NBR_TABLE_CONF_MAX_NEIGHBORS      20
#define UIP_CONF_DS6_DEFRT_NBU    2
#define UIP_CONF_DS6_PREFIX_NBU   3
#define UIP_CONF_MAX_ROUTES    4
#define UIP_CONF_DS6_ADDR_NBU     3
#define UIP_CONF_DS6_MADDR_NBU    0
#define UIP_CONF_DS6_AADDR_NBU    0


#elif 1  /* cx-mac radio cycling */
/* RF230 does clear-channel assessment in extended mode (autoretries>0) */
/* These values are guesses */
#define RF230_CONF_FRAME_RETRIES  10
#define RF230_CONF_CSMA_RETRIES   2
#if RF230_CONF_CSMA_RETRIES
#define NETSTACK_CONF_MAC         nullmac_driver
#else
#define NETSTACK_CONF_MAC         csma_driver
#endif
#define NETSTACK_CONF_RDC         cxmac_driver
#define NETSTACK_CONF_FRAMER      framer_802154
#define NETSTACK_CONF_RADIO       rf230_driver
#define CHANNEL_802_15_4          26
#define RF230_CONF_AUTOACK        1
#define SICSLOWPAN_CONF_FRAG      1
#define SICSLOWPAN_CONF_MAXAGE    3
#define CXMAC_CONF_ANNOUNCEMENTS  0
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8
/* 211 bytes per queue buffer. Burst mode will need 15 for a 1280 byte MTU */
#define QUEUEBUF_CONF_NUM         15
/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2
/* Allocate remaining RAM. Not much left due to queuebuf increase  */
#define UIP_CONF_MAX_CONNECTIONS  2
#define UIP_CONF_MAX_LISTENPORTS  4
#define UIP_CONF_UDP_CONNS        5
#define NBR_TABLE_CONF_MAX_NEIGHBORS      4
#define UIP_CONF_DS6_DEFRT_NBU    2
#define UIP_CONF_DS6_PREFIX_NBU   3
#define UIP_CONF_MAX_ROUTES    4
#define UIP_CONF_DS6_ADDR_NBU     3
#define UIP_CONF_DS6_MADDR_NBU    0
#define UIP_CONF_DS6_AADDR_NBU    0
//Below gives 10% duty cycle, undef for default 5%
//#define CXMAC_CONF_ON_TIME (RTIMER_ARCH_SECOND / 80)
//Below gives 50% duty cycle
//#define CXMAC_CONF_ON_TIME (RTIMER_ARCH_SECOND / 16)

#else
#error Network configuration not specified!
#endif   /* Network setup */

/* ************************************************************************** */
//#pragma mark RPL Settings
/* ************************************************************************** */
#if UIP_CONF_IPV6_RPL

#define UIP_CONF_ROUTER                 1
#define UIP_CONF_ND6_SEND_RA		    0
#define UIP_CONF_ND6_REACHABLE_TIME     600000
#define UIP_CONF_ND6_RETRANS_TIMER      10000

/* For slow slip connections, to prevent buffer overruns */
//#define UIP_CONF_RECEIVE_WINDOW 300
#undef UIP_CONF_FWCACHE_SIZE
#define UIP_CONF_FWCACHE_SIZE    30
#define UIP_CONF_BROADCAST       1
#define UIP_ARCH_IPCHKSUM        1
#define UIP_CONF_PINGADDRCONF    0
#define UIP_CONF_LOGGING         0

#endif /* RPL */

#define CCIF
#define CLIF
#ifndef CC_CONF_INLINE
#define CC_CONF_INLINE inline
#endif

/* include the project config */
/* PROJECT_CONF_H might be defined in the project Makefile */
#ifdef PROJECT_CONF_H
#include PROJECT_CONF_H
#endif

#endif /* CONTIKI_CONF_H_ */
