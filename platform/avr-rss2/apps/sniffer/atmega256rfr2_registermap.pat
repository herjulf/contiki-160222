diff --git a/cpu/avr/radio/rf230bb/atmega256rfr2_registermap.h b/cpu/avr/radio/rf230bb/atmega256rfr2_registermap.h
index b373711..bc737de 100644
--- a/cpu/avr/radio/rf230bb/atmega256rfr2_registermap.h
+++ b/cpu/avr/radio/rf230bb/atmega256rfr2_registermap.h
@@ -73,6 +73,7 @@
 #define SR_RSSI               0x146, 0x1f, 0
 #define SR_RX_SYN             0x155, 0xff, 0
 #define SR_TRX_RPC            0x156, 0xff, 0
+#define SR_XAH_CTRL_1         0x157, 0xf5, 2
 #define SR_PLL_CF_START       0x15a, 0x80, 7
 #define SR_PLL_DCU_START      0x15b, 0x80, 7
 #define SR_MAX_CSMA_RETRIES   0x16c, 0x0e, 1
@@ -84,7 +85,7 @@
 #define SR_CCA_DONE            0x141, 0x80, 7
 #define SR_CCA_STATUS          0x141, 0x40, 6
 #define SR_AACK_SET_PD         0x16e, 0x20, 5
-
+#define SR_CSMA_SEED_1         0x16e, 0x10, 4
 
 /* RF230 register assignments, for reference */
 #if 1
