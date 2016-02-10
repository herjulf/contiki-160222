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
 *
 */

package se.sics.cooja.avrmote;

import se.sics.cooja.AbstractionLevelDescription;
import se.sics.cooja.ClassDescription;
import se.sics.cooja.Mote;
import se.sics.cooja.MoteInterface;
import se.sics.cooja.Simulation;
import se.sics.cooja.avrmote.interfaces.AvroraADC;
import se.sics.cooja.avrmote.interfaces.AvroraClock;
import se.sics.cooja.avrmote.interfaces.AvroraLED;
import se.sics.cooja.avrmote.interfaces.AvroraMoteID;
import se.sics.cooja.avrmote.interfaces.AvroraUsart0;
import se.sics.cooja.avrmote.interfaces.RFR2Radio;
import se.sics.cooja.interfaces.IPAddress;
import se.sics.cooja.interfaces.Mote2MoteRelations;
import se.sics.cooja.interfaces.MoteAttributes;
import se.sics.cooja.interfaces.Position;
import se.sics.cooja.interfaces.RimeAddress;
import se.sics.cooja.GUI;

import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.Toolkit;
import java.io.File;
import java.net.URL;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;

/**
 * RSS2 (Radio-Sensors.com) mote with AtMega256RFR2 emulated in Avrora.
 *
 * @author Joakim Eriksson, Fredrik Osterlind, David Kopf, Atis Elsts
 */
@ClassDescription("RSS2 Mote Type")
@AbstractionLevelDescription("Emulated level")
public class RSS2MoteType extends AvroraMoteType {

  // The returned string is used for mote type name and icon jpg file
  public final String getMoteName() {
    return ("RSS2");
  }
  // The returned string is used for firmware file extension
  public final String getMoteContikiTarget() {
    return ("avr-rss2");
  }

  public final Mote generateMote(Simulation simulation) {
    RSS2Mote mote = new RSS2Mote(simulation, this);
    mote.initMote();
    return mote;
  }

  public Icon getMoteTypeIcon() {
    Toolkit toolkit = Toolkit.getDefaultToolkit();
    URL imageURL = this.getClass().getClassLoader().getResource("images/rss2.jpg");
    Image image = toolkit.getImage(imageURL);
    MediaTracker tracker = new MediaTracker(GUI.getTopParentContainer());
    tracker.addImage(image, 1);
    try {
      tracker.waitForAll();
    } catch (InterruptedException ex) {
    }
    if (image.getHeight(GUI.getTopParentContainer()) > 0 && image.getWidth(GUI.getTopParentContainer()) > 0) {
      image = image.getScaledInstance((200*image.getWidth(GUI.getTopParentContainer())/image.getHeight(GUI.getTopParentContainer())), 200, Image.SCALE_DEFAULT);
      return new ImageIcon(image);
    }

    return null;
  }

  /* Note the ADC and Debugger interfaces are also an extension of Clock and
   * will get the setDrift/getDrift calls for random startup if included before
   * the Clock interface. The clock would then show zero drift.
   */
 @SuppressWarnings("unchecked")
 public Class<? extends MoteInterface>[] getAllMoteInterfaceClasses() {
    return new Class[] {
        Position.class,
        AvroraMoteID.class,
        AvroraLED.class,
        RFR2Radio.class,
        AvroraClock.class,
        AvroraUsart0.class,
        AvroraADC.class,
        Mote2MoteRelations.class,
        MoteAttributes.class,
        RimeAddress.class,
        IPAddress.class
    };

  }

}
