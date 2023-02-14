#include <esp_bt.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#ifndef CONFIG_CLASSIC_BT_ENABLED
#error Need CLASSIC BT.
#endif

#define PSM_HID_Control_11   0x0011
#define PSM_HID_Interrupt_13 0x0013

#define RX_QUEUE_SIZE 32
#define TX_QUEUE_SIZE 32

#define FORMAT_HEX_MAX_BYTES 30
