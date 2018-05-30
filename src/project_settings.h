#ifndef SRC_PROJECT_SETTINGS_H_
#define SRC_PROJECT_SETTINGS_H_

/* Defines application keys and other settings
 * The lorawan library was hacked to include this file for its macros concerning keys etc.
 *
 * Care must be taken that this header is included everwhere where these macros are used!
 * otherwise default settings from the board variant will kick in.
 *
 * Must be double checked some time later
 * */

/* undefine everything previously set */
#ifdef MBED_CONF_LORA_DEVICE_EUI
#undef MBED_CONF_LORA_DEVICE_EUI
#endif

#ifdef MBED_CONF_LORA_APPLICATION_KEY
#undef MBED_CONF_LORA_APPLICATION_KEY
#endif

#ifdef MBED_CONF_LORA_PHY
#undef MBED_CONF_LORA_PHY
#endif

#ifdef MBED_CONF_LORA_DEVICE_ADDRESS
#undef MBED_CONF_LORA_DEVICE_ADDRESS
#endif

#ifdef MBED_CONF_LORA_NWKSKEY
#undef MBED_CONF_LORA_NWKSKEY
#endif

#ifdef MBED_CONF_LORA_APPSKEY
#undef MBED_CONF_LORA_APPSKEY
#endif

#ifdef MBED_CONF_LORA_OVER_THE_AIR_ACTIVATION
#undef MBED_CONF_LORA_OVER_THE_AIR_ACTIVATION
#endif

#ifdef MBED_CONF_LORA_TX_MAX_SIZE
#undef MBED_CONF_LORA_TX_MAX_SIZE
#endif

#ifdef MBED_CONF_LORA_APPLICATION_EUI
#undef MBED_CONF_LORA_APPLICATION_EUI
#endif

#define MBED_CONF_LORA_DEVICE_EUI {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#define MBED_CONF_LORA_APPLICATION_EUI {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define MBED_CONF_LORA_APPLICATION_KEY {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
/* 0 = EU868, see LoRa PHY headers */
#define MBED_CONF_LORA_PHY 0
#define MBED_CONF_LORA_DEVICE_ADDRESS 0x26011BA3
#define MBED_CONF_LORA_NWKSKEY { 0xFC, 0x94, 0xC8, 0x2C, 0x72, 0x42, 0x1B, 0xEA, 0xCA, 0x3F, 0xFE, 0x71, 0x37, 0xE1, 0x15, 0x59 }
#define MBED_CONF_LORA_APPSKEY { 0xF4, 0x44, 0xD6, 0x45, 0xBB, 0xFA, 0xB0, 0xE9, 0x2C, 0xAC, 0xB7, 0xD9, 0x61, 0x0E, 0x90, 0x87 }
/* if 0 uses ABP, else OTAA */
#define MBED_CONF_LORA_OVER_THE_AIR_ACTIVATION 0
/* by default only 64. max allowed on SF7 is 255 (for complete frame). */
#define MBED_CONF_LORA_TX_MAX_SIZE 255

/* other important app settings */
#define LORA_TX_SF	(9) /* SF to start transmitting at. Valid from 7 to 12. */

/* send (queue) something every 10 seconds.
 * actual pushed out data depends on the current SF. */
#define SENDER_TX_MILLIS (10 * 1000)


#endif /* SRC_PROJECT_SETTINGS_H_ */
