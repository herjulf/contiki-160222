/*
 * Copyright (c) 2012, Swedish Institute of Computer Science.
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
 */

package avrora.sim.radio;

import avrora.sim.radio.ATmega128RFA1Radio;
import avrora.sim.mcu.Microcontroller;

/**
 * The <code>ATmega256RFR2Radio</code> implements a simulation of the internal
 * radio of the ATmega256RFR2 chip.
 * Verbose printers for this class include "radio.rfr2"
 *
 * @author Atis Elsts
 */
public class ATmega256RFR2Radio extends ATmega128RFA1Radio {

    // Empty implementation for now
    // TODO: implement the changes compared to the base class


    /**
     * The constructor for the ATmega256RFR2Radio class creates a new instance internal
     * to the specified microcontroller with the given clock frequency.
     *
     * @param mcu   the microcontroller unit in which this radio resides
     * @param xfreq the clock frequency of this microcontroller
     */
    public ATmega256RFR2Radio(Microcontroller mcu, int xfreq) {
        super(mcu, xfreq);
    }
}
