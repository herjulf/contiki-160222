/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
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
 * $Id: ContikiRadio.java,v 1.32 2010/03/09 08:11:05 fros4943 Exp $
 */

package se.sics.cooja.contikimote.interfaces;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collection;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.apache.log4j.Logger;
import org.jdom.Element;

import se.sics.cooja.COOJARadioPacket;
import se.sics.cooja.Mote;
import se.sics.cooja.RadioPacket;
import se.sics.cooja.SectionMoteMemory;
import se.sics.cooja.Simulation;
import se.sics.cooja.contikimote.ContikiMote;
import se.sics.cooja.contikimote.ContikiMoteInterface;
import se.sics.cooja.interfaces.PolledAfterActiveTicks;
import se.sics.cooja.interfaces.Position;
import se.sics.cooja.interfaces.Radio;
import se.sics.cooja.radiomediums.UDGM;

/**
 * Packet radio transceiver mote interface.
 *
 * To simulate transmission rates, the underlying Contiki system is
 * locked in TX or RX states using multi-threading library.
 *
 * Contiki variables:
 * <ul>
 * <li>char simReceiving (1=mote radio is receiving)
 * <li>char simInPolled
 * <p>
 * <li>int simInSize (size of received data packet)
 * <li>byte[] simInDataBuffer (data of received data packet)
 * <p>
 * <li>int simOutSize (size of transmitted data packet)
 * <li>byte[] simOutDataBuffer (data of transmitted data packet)
 * <p>
 * <li>char simRadioHWOn (radio hardware status (on/off))
 * <li>int simSignalStrength (heard radio signal strength)
 * <li>int simLastSignalStrength
 * <li>char simPower (number indicating power output)
 * <li>int simRadioChannel (number indicating current channel)
 * </ul>
 * <p>
 *
 * Core interface:
 * <ul>
 * <li>radio_interface
 * </ul>
 * <p>
 *
 * This observable notifies at radio state changes during RX and TX.
 *
 * @see #getLastEvent()
 * @see UDGM
 *
 * @author Fredrik Osterlind
 */
public class ContikiRadio extends Radio implements ContikiMoteInterface, PolledAfterActiveTicks {
  private ContikiMote mote;

  private SectionMoteMemory myMoteMemory;

  private static Logger logger = Logger.getLogger(ContikiRadio.class);

  /**
   * Transmission bitrate (kbps).
   */
  public final double RADIO_TRANSMISSION_RATE_kbps;

  private RadioPacket packetToMote = null;

  private RadioPacket packetFromMote = null;

  private boolean radioOn = true;

  private boolean isTransmitting = false;
  private boolean isSendingAck = false;
//private boolean isReceivingAck = false;
  private byte[] ackPacket = null;
  private long ackStartTime;
  private long receptionStartTime;

  private boolean isInterfered = false;

  private long transmissionEndTime = -1;

  private RadioEvent lastEvent = RadioEvent.UNKNOWN;

  private long lastEventTime = 0;

  private int oldOutputPowerIndicator = -1;

  /**
   * Creates an interface to the radio at mote.
   *
   * @param mote Mote
   *
   * @see Mote
   * @see se.sics.cooja.MoteInterfaceHandler
   */
  public ContikiRadio(Mote mote) {
    // Read class configurations of this mote type
    RADIO_TRANSMISSION_RATE_kbps = mote.getType().getConfig().getDoubleValue(
        ContikiRadio.class, "RADIO_TRANSMISSION_RATE_kbps");

    this.mote = (ContikiMote) mote;
    this.myMoteMemory = (SectionMoteMemory) mote.getMemory();

    radioOn = myMoteMemory.getByteValueOf("simRadioHWOn") == 1;
  }

  /* Contiki mote interface support */
  public static String[] getCoreInterfaceDependencies() {
    return new String[] { "radio_interface" };
  }

  /* Packet radio support */
  public RadioPacket getLastPacketTransmitted() {
    return packetFromMote;
  }

  public RadioPacket getLastPacketReceived() {
    return packetToMote;
  }

  public void setReceivedPacket(RadioPacket packet) {
    packetToMote = packet;
  }

  /* General radio support */
  public boolean isRadioOn() {
    return radioOn;
  }
  public boolean isListening() {
	return radioOn;
  }

  public boolean isTransmitting() {
    return isTransmitting;
  }

  public boolean isReceiving() {
    return myMoteMemory.getByteValueOf("simReceiving") == 1;
  }

  public boolean isInterfered() {
    return isInterfered;
  }

  public int getChannel() {
    return myMoteMemory.getIntValueOf("simRadioChannel");
  }

  public void signalReceptionStart() {
    packetToMote = null;
    if (isInterfered() || isReceiving() || isTransmitting()) {
      interfereAnyReception();
      return;
    }
    if (isSendingAck) return;
    receptionStartTime =  mote.getSimulation().getSimulationTime();
    if (!radioOn) {System.out.println("sleeping");return;}
    myMoteMemory.setByteValueOf("simReceiving", (byte) 1);
    mote.requestImmediateWakeup();

    lastEventTime = mote.getSimulation().getSimulationTime();
    lastEvent = RadioEvent.RECEPTION_STARTED;

    this.setChanged();
    this.notifyObservers();
  }

  public void signalReceptionEnd() {
      long now = mote.getSimulation().getSimulationTime();
    if (isInterfered || packetToMote == null) {
      isInterfered = false;
      packetToMote = null;
      myMoteMemory.setIntValueOf("simInSize", 0);
    } else if (!radioOn) {
        System.out.println("radio off at receptionend " + now);
        return;
    } else {
      myMoteMemory.setIntValueOf("simInSize", packetToMote.getPacketData().length);
      myMoteMemory.setByteArray("simInDataBuffer", packetToMote.getPacketData());
    }

    myMoteMemory.setByteValueOf("simReceiving", (byte) 0);
 //   mote.requestImmediateWakeup();
    lastEventTime = now;
    lastEvent = RadioEvent.RECEPTION_FINISHED;
    this.setChanged();
    this.notifyObservers();

    /* Send ack if requested */
    /*TODO:address match!*/
    if (packetToMote != null) {
        byte packetData[] = packetToMote.getPacketData();
        if ((packetData[0] & 0x20) == 0) return;
        
        isSendingAck = true;
        if (ackPacket == null) {
            ackPacket = new byte[5];
            ackPacket[0] = 0x02;
            ackPacket[1] = 0x00;
        }
        ackPacket[2] = packetData[2]; //seqno
        short acc = 13232;
        acc ^= 0xff & ackPacket[2];
        acc  = (short) ((0xff & (acc >> 8)) | (0xff00 & (acc << 8)));
        acc ^= 0xffff & ((acc & 0xff00) << 4);
        acc ^= (0xffff & (0xff & (acc >> 8)) >> 4);
        acc ^= 0xffff & ((0xffff & (acc & 0xff00)) >>> 5);
        ackPacket[4] = (byte) ((acc >> 8) &0xFF);
        ackPacket[3] = (byte) (acc & 0xFF);

        packetFromMote = new COOJARadioPacket(ackPacket);
        // Calculate start time of ack based on the time the received packet started
        long duration = (int) (Simulation.MILLISECOND*((8 * (6 + packetData.length)) ) / RADIO_TRANSMISSION_RATE_kbps);
        System.out.println("packet length is " + packetData.length + " duration " + duration);
        ackStartTime = receptionStartTime + duration + 192;
     // System.out.println("now " + now + " packet length " + packetData.length + "duration " + duration + "ackstarttime " + ackStartTime);
        if (now > ackStartTime) {
        //fall through to wakeup
        } else {
            mote.scheduleNextWakeup(ackStartTime);
            return;
        }
    }
  //   myMoteMemory.setByteValueOf("simReceiving", (byte) 0);
     mote.requestImmediateWakeup();
  }

  public RadioEvent getLastEvent() {
    return lastEvent;
  }

  public void interfereAnyReception() {
    if (isInterfered()) {
      return;
    }
 
    isInterfered = true;

    lastEvent = RadioEvent.RECEPTION_INTERFERED;
    lastEventTime = mote.getSimulation().getSimulationTime();
    this.setChanged();
    this.notifyObservers();
  }

  public double getCurrentOutputPower() {
    /* TODO Implement method */
    logger.warn("Not implemented, always returning 0 dBm");
    return 0;
  }

  public int getOutputPowerIndicatorMax() {
    return 100;
  }

  public int getCurrentOutputPowerIndicator() {
    return myMoteMemory.getByteValueOf("simPower");
  }

  public double getCurrentSignalStrength() {
    return myMoteMemory.getIntValueOf("simSignalStrength");
  }

  public void setCurrentSignalStrength(double signalStrength) {
    myMoteMemory.setIntValueOf("simSignalStrength", (int) signalStrength);
  }

  public Position getPosition() {
    return mote.getInterfaces().getPosition();
  }

  public void doActionsAfterTick() {
    long now = mote.getSimulation().getSimulationTime();
  
    /* Timing chain to send an ack */
    if (isSendingAck) {
        if (isTransmitting) {
            if (now >= transmissionEndTime) {
                // all done. Should mote wake?
                isSendingAck = false;
                isTransmitting = false;
                mote.requestImmediateWakeup();
                lastEventTime = now;
                lastEvent = RadioEvent.TRANSMISSION_FINISHED;
                this.setChanged();
                this.notifyObservers();
            } else {
                // wait until end time
                mote.scheduleNextWakeup(transmissionEndTime);
                return;
            }
        } else if (now >= ackStartTime) {
            // start sending the ack
            isTransmitting = true;
            lastEvent = RadioEvent.TRANSMISSION_STARTED;
            lastEventTime = now;
            this.setChanged();
            this.notifyObservers();
            lastEvent = RadioEvent.PACKET_TRANSMITTED;
            this.setChanged();
            this.notifyObservers();
            //ack transmit time is 352 usec at 250Kibs
            long duration = (int) (Simulation.MILLISECOND*((8 * (6 + 5) ) / RADIO_TRANSMISSION_RATE_kbps));
            transmissionEndTime = now + duration;
            mote.scheduleNextWakeup(transmissionEndTime);
            return;
        } else {
            // maybe this should fall through
            mote.scheduleNextWakeup(ackStartTime);
            return;
        }

    }
    /* Check if radio hardware status changed */
    if (radioOn != (myMoteMemory.getByteValueOf("simRadioHWOn") == 1)) {
      if (isSendingAck) {
  //      System.out.println("radio turned off before sending ack");
      }
      radioOn = !radioOn;
      isSendingAck = false;
      isTransmitting = false;

      if (!radioOn) {
        myMoteMemory.setByteValueOf("simReceiving", (byte) 0);
        myMoteMemory.setIntValueOf("simInSize", 0);
        myMoteMemory.setIntValueOf("simOutSize", 0);
        lastEvent = RadioEvent.HW_OFF;
      } else {
        lastEvent = RadioEvent.HW_ON;
      }

      lastEventTime = now;
      this.setChanged();
      this.notifyObservers();
    }
    if (!radioOn) {
      return;
    }

    /* Check if radio output power changed */
    if (myMoteMemory.getByteValueOf("simPower") != oldOutputPowerIndicator) {
      oldOutputPowerIndicator = myMoteMemory.getByteValueOf("simPower");
      lastEvent = RadioEvent.UNKNOWN;
      this.setChanged();
      this.notifyObservers();
    }


    /* Ongoing transmission */
    if (isTransmitting && now >= transmissionEndTime) {
      myMoteMemory.setIntValueOf("simOutSize", 0);
      isTransmitting = false;
      mote.requestImmediateWakeup();

      lastEventTime = now;
      lastEvent = RadioEvent.TRANSMISSION_FINISHED;
      this.setChanged();
      this.notifyObservers();
      /*logger.debug("----- CONTIKI TRANSMISSION ENDED -----");*/
    }

    /* New transmission */
    int size = myMoteMemory.getIntValueOf("simOutSize");
    if (!isTransmitting && size > 0) {

      packetFromMote = new COOJARadioPacket(myMoteMemory.getByteArray("simOutDataBuffer", size));
      if (packetFromMote.getPacketData() == null || packetFromMote.getPacketData().length == 0) {
        logger.warn("Skipping zero sized Contiki packet (no buffer)");
        myMoteMemory.setIntValueOf("simOutSize", 0);
        mote.requestImmediateWakeup();
        return;
      }

      isTransmitting = true;
      myMoteMemory.setByteValueOf("simReceiving", (byte) 0);

      /* Calculate transmission duration (us) */
      /* XXX Currently floored due to millisecond scheduling! */
      long duration = (int) (Simulation.MILLISECOND*((8 * size /*bits*/) / RADIO_TRANSMISSION_RATE_kbps));
      //truncation will turn radio off before end time, so add 1 millisecond
 //   transmissionEndTime = now + Math.max(1, duration);
      transmissionEndTime = now + duration + 1000;

      lastEventTime = now;
      lastEvent = RadioEvent.TRANSMISSION_STARTED;

      this.setChanged();
      this.notifyObservers();
      //logger.debug("----- NEW CONTIKI TRANSMISSION DETECTED -----");

      // Deliver packet right away
      lastEvent = RadioEvent.PACKET_TRANSMITTED;
      this.setChanged();
      this.notifyObservers();
      //logger.debug("----- CONTIKI PACKET DELIVERED -----");
    if (isTransmitting && transmissionEndTime > now) {
      mote.scheduleNextWakeup(transmissionEndTime);
    }
    }
  }

  public Collection<Element> getConfigXML() {
    return null;
  }

  public void setConfigXML(Collection<Element> configXML, boolean visAvailable) {
  }

  public Mote getMote() {
    return mote;
  }

  public String toString() {
    return "Radio at " + mote;
  }
}
