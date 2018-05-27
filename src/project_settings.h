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
#define MBED_CONF_LORA_DEVICE_ADDRESS 0x00000000
#define MBED_CONF_LORA_NWKSKEY { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define MBED_CONF_LORA_APPSKEY { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
/* if 0 uses ABP, else OTAA */
#define MBED_CONF_LORA_OVER_THE_AIR_ACTIVATION 0
/* by default only 64. max allowed on SF7 is 255 (for complete frame). */
#define MBED_CONF_LORA_TX_MAX_SIZE 255

/* other important app settings */
#define LORA_TX_SF	(9) /* SF to start transmitting at. Valid from 7 to 12. */


#endif /* SRC_PROJECT_SETTINGS_H_ */
