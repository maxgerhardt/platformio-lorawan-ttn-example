/*
 * LoRaWANStack.h
 *
 *  Created on: 27.05.2018
 *      Author: Maxi
 */

#ifndef SRC_LORAWANSTACK_H_
#define SRC_LORAWANSTACK_H_

#include <stdint.h>
#include <stddef.h>

typedef void (*receive_func_t)(const uint8_t* data, size_t len);

int LoRaWANStack_Init();

bool LoRaWANStack_Send(uint8_t fport, const uint8_t* data, size_t len, bool confirmed = false);

bool LoRaWAN_SendingInProgress();

void LoRaWANStack_InstallReceiveCB(receive_func_t func);

void LoRaWANStack_ServeForever();

uint8_t ConvertSFToDR(int sf);

#endif /* SRC_LORAWANSTACK_H_ */
