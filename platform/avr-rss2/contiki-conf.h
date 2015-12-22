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

/* include the project config */
/* PROJECT_CONF_H might be defined in the project Makefile */
#ifdef PROJECT_CONF_H
#include PROJECT_CONF_H
#endif

/* Platform name, type, and MCU clock rate */
#define PLATFORM_NAME  "rss2"
#define PLATFORM_TYPE  ATMEGA256RFR2
#ifndef F_CPU
#define F_CPU          8000000UL
#endif

#include <stdint.h>

#ifndef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC     csma_driver
#endif

#ifndef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC     contikimac_driver
#endif

#ifndef NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8
#endif

#ifndef NETSTACK_CONF_FRAMER
#if NETSTACK_CONF_WITH_IPV6
#define NETSTACK_CONF_FRAMER  contikimac_framer
#else
#define NETSTACK_CONF_FRAMER  framer_802154
#endif
#endif

#ifndef NETSTACK_CONF_RADIO
#define NETSTACK_CONF_RADIO   rf230_driver
#endif

#ifndef CHANNEL_802_15_4
#define CHANNEL_802_15_4      26
#endif

/* AUTOACK receive mode gives better rssi measurements, even if ACK is never requested */
#ifndef RF230_CONF_AUTOACK
#define RF230_CONF_AUTOACK        1
#endif

#define MCUCSR  MCUSR

/* The AVR tick interrupt usually is done with an 8 bit counter around 128 Hz.
 * 125 Hz needs slightly more overhead during the interrupt, as does a 32 bit
 * clock_time_t.
 */
/* Clock ticks per second */

#define CLOCK_CONF_SECOND 128
typedef unsigned long clock_time_t;
#define CLOCK_LT(a, b)  ((signed long)((a) - (b)) < 0)
#define INFINITE_TIME 0xffffffff
/* These routines are not part of the contiki core but can be enabled in cpu/avr/clock.c */
void clock_delay_msec(uint16_t howlong);
void clock_adjust_ticks(clock_time_t howmany);

/* The radio needs to interrupt during an rtimer interrupt */
#define RTIMER_CONF_NESTED_INTERRUPTS 1

/* RSS2 boards has a 32768Hz on TIMER2 */
#define AVR_CONF_USE32KCRYSTAL 1
#define SLIP_PORT RS232_PORT_0

/* Pre-allocated memory for loadable modules heap space (in bytes)*/
/* Default is 4096. Currently used only when elfloader is present. Not tested on Raven */
/* #define MMEM_CONF_SIZE 256 */

/* Starting address for code received via the codeprop facility. Not tested. */
typedef unsigned long off_t;
/* Logging adds 200 bytes to program size. RS232 output slows down webserver. */
/* #define LOG_CONF_ENABLED         1 */

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
/* #define WATCHDOG_CONF_TIMEOUT -1 */

/* Debugflow macro, useful for tracing path through mac and radio interrupts */
/* #define DEBUGFLOWSIZE 128 */

/* Define MAX_*X_POWER to reduce tx power and ignore weak rx packets for testing a miniature multihop network.
 * Leave undefined for full power and sensitivity.
 * tx=0 (3dbm, default) to 15 (-17.2dbm)
 * RF230_CONF_AUTOACK sets the extended mode using the energy-detect register with rx=0 (-91dBm) to 84 (-7dBm)
 *   else the rssi register is used having range 0 (91dBm) to 28 (-10dBm)
 *   For simplicity RF230_MIN_RX_POWER is based on the energy-detect value and divided by 3 when autoack is not set.
 * On the RF230 a reduced rx power threshold will not prevent autoack if enabled and requested.
 * These numbers applied to both Raven and Jackdaw give a maximum communication distance of about 15 cm
 * and a 10 meter range to a full-sensitivity RF230 sniffer.
 *#define RF230_MAX_TX_POWER 15
 *#define RF230_MIN_RX_POWER 30
 */
/* The rf231 and atmega128rfa1 can use an rssi threshold for triggering rx_busy that saves 0.5ma in rx mode */
/* 1 - 15 maps into -90 to -48 dBm; the register is written with RF230_MIN_RX_POWER/6 + 1. Undefine for -100dBm sensitivity */
/* #define RF230_MIN_RX_POWER        0 */

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
#ifndef UIP_CONF_TCP
#define UIP_CONF_TCP              1
#endif
#define NETSTACK_CONF_NETWORK     sicslowpan_driver
#define SICSLOWPAN_CONF_COMPRESSION SICSLOWPAN_COMPRESSION_HC06
#else
/* ip4 should build but is largely untested */
#define LINKADDR_CONF_SIZE        2
#define NETSTACK_CONF_NETWORK     rime_driver
#endif

#if UIP_CONF_IPV6_RPL
#define UIP_CONF_BUFFER_SIZE   600 /*  DHCPv4 packets by ip64 module */
#endif /* RPL */

#define CCIF
#define CLIF
#ifndef CC_CONF_INLINE
#define CC_CONF_INLINE inline
#endif

#endif /* CONTIKI_CONF_H_ */
