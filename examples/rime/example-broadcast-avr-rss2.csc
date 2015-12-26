<?xml version="1.0" encoding="UTF-8"?>
<simconf>
  <project EXPORT="discard">[CONTIKI_DIR]/tools/cooja/apps/mrm</project>
  <project EXPORT="discard">[CONTIKI_DIR]/tools/cooja/apps/mspsim</project>
  <project EXPORT="discard">[CONTIKI_DIR]/tools/cooja/apps/avrora</project>
  <project EXPORT="discard">[CONTIKI_DIR]/tools/cooja/apps/native_gateway</project>
  <project EXPORT="discard">[CONTIKI_DIR]/tools/cooja/apps/serial_socket</project>
  <project EXPORT="discard">/home/user/contikiprojects/sics.se/mobility</project>
  <project EXPORT="discard">[CONTIKI_DIR]/tools/cooja/apps/collect-view</project>
  <project EXPORT="discard">/home/user/contikiprojects/sics.se/powertracker</project>
  <simulation>
    <title>Broadcast example</title>
    <delaytime>0</delaytime>
    <randomseed>123456</randomseed>
    <motedelay_us>1000000</motedelay_us>
    <radiomedium>
      se.sics.cooja.radiomediums.UDGM
      <transmitting_range>50.0</transmitting_range>
      <interference_range>100.0</interference_range>
      <success_ratio_tx>1.0</success_ratio_tx>
      <success_ratio_rx>1.0</success_ratio_rx>
    </radiomedium>
    <events>
      <logoutput>40000</logoutput>
    </events>
    <motetype>
      se.sics.cooja.avrmote.RSS2MoteType
      <identifier>mote1</identifier>
      <description>Broadcast example</description>
      <source EXPORT="discard">[CONTIKI_DIR]/examples/rime/example-broadcast.c</source>
      <commands EXPORT="discard">make example-broadcast.avr-rss2 TARGET=avr-rss2</commands>
      <firmware EXPORT="copy">[CONTIKI_DIR]/examples/rime/example-broadcast.avr-rss2</firmware>
      <moteinterface>se.sics.cooja.interfaces.Position</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraClock</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraMoteID</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraUsart0</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraUsart1</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.RFR2Radio</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraADC</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraLED</moteinterface>
    </motetype>
    <motetype>
      se.sics.cooja.avrmote.RSS2MoteType
      <identifier>mote2</identifier>
      <description>Broadcast example</description>
      <source EXPORT="discard">[CONTIKI_DIR]/examples/rime/example-broadcast.c</source>
      <commands EXPORT="discard">make example-broadcast.avr-atmega128rfa1 TARGET=avr-atmega128rfa1</commands>
      <firmware EXPORT="copy">[CONTIKI_DIR]/examples/rime/example-broadcast.avr-atmega128rfa1</firmware>
      <moteinterface>se.sics.cooja.interfaces.Position</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>se.sics.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraClock</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraMoteID</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraUsart0</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraUsart1</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.RFR2Radio</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraADC</moteinterface>
      <moteinterface>se.sics.cooja.avrmote.interfaces.AvroraLED</moteinterface>
    </motetype>
    <mote>
      <breakpoints />
      <interface_config>
        se.sics.cooja.interfaces.Position
        <x>37.5366545201821</x>
        <y>20.133438936240488</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        se.sics.cooja.avrmote.interfaces.AvroraMoteID
        <id>1</id>
      </interface_config>
      <motetype_identifier>mote1</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        se.sics.cooja.interfaces.Position
        <x>50.05393308569106</x>
        <y>3.886106972235548</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        se.sics.cooja.avrmote.interfaces.AvroraMoteID
        <id>2</id>
      </interface_config>
      <motetype_identifier>mote1</motetype_identifier>
    </mote>
  </simulation>
  <plugin>
    se.sics.cooja.plugins.SimControl
    <width>318</width>
    <z>3</z>
    <height>192</height>
    <location_x>0</location_x>
    <location_y>0</location_y>
  </plugin>
  <plugin>
    se.sics.cooja.plugins.Visualizer
    <plugin_config>
      <skin>se.sics.cooja.plugins.skins.IDVisualizerSkin</skin>
      <skin>se.sics.cooja.plugins.skins.AddressVisualizerSkin</skin>
      <skin>se.sics.cooja.plugins.skins.UDGMVisualizerSkin</skin>
      <viewport>2.6322285313650773 0.0 0.0 2.6322285313650773 36.20636526098638 1.3163328971993926</viewport>
    </plugin_config>
    <width>300</width>
    <z>1</z>
    <height>300</height>
    <location_x>528</location_x>
    <location_y>-2</location_y>
  </plugin>
  <plugin>
    se.sics.cooja.plugins.LogListener
    <plugin_config>
      <filter />
    </plugin_config>
    <width>827</width>
    <z>2</z>
    <height>218</height>
    <location_x>1</location_x>
    <location_y>197</location_y>
  </plugin>
  <plugin>
    se.sics.cooja.plugins.TimeLine
    <plugin_config>
      <mote>0</mote>
      <mote>1</mote>
      <showRadioRXTX />
      <showRadioHW />
      <split>125</split>
      <zoomfactor>500.0</zoomfactor>
    </plugin_config>
    <width>828</width>
    <z>0</z>
    <height>138</height>
    <location_x>0</location_x>
    <location_y>414</location_y>
  </plugin>
</simconf>

