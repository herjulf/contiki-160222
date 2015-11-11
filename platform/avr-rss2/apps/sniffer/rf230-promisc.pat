diff --git a/cpu/avr/radio/rf230bb/rf230bb.c b/cpu/avr/radio/rf230bb/rf230bb.c
index 53959d1..d4f63a0 100644
--- a/cpu/avr/radio/rf230bb/rf230bb.c
+++ b/cpu/avr/radio/rf230bb/rf230bb.c
@@ -544,7 +544,7 @@ rf230_set_promiscuous_mode(bool isPromiscuous) {
 #if RF230_CONF_AUTOACK
     is_promiscuous = isPromiscuous;
 /* TODO: Figure out when to pass promisc state to 802.15.4 */
-//    radio_set_trx_state(is_promiscuous?RX_ON:RX_AACK_ON);
+    radio_set_trx_state(is_promiscuous?RX_ON:RX_AACK_ON);
 #endif
 }
 
@@ -1392,6 +1392,25 @@ PROCESS_THREAD(rf230_process, ev, data)
     /* Restore interrupts. */
     HAL_LEAVE_CRITICAL_REGION();
     PRINTF("rf230_read: %u bytes lqi %u\n",len,rf230_last_correlation);
+
+    if(is_promiscuous) {
+      uint8_t i;
+      unsigned const char * rxdata = packetbuf_dataptr();
+      /* Print magic */
+      rs232_send(0, 0xC1);
+      rs232_send(0, 0x1F);
+      rs232_send(0, 0xFE);
+      rs232_send(0, 0x72);
+      /* Print version */
+      rs232_send(0, 0x01);
+      /* Print CMD == frame */
+      rs232_send(0, 0x00);
+      rs232_send(0, len+2);
+
+      for (i=0;i<len+2;i++)  rs232_send(0, rxdata[i]);
+      printf("\n");
+    }
+
 #if DEBUG>1
      {
         uint8_t i;
