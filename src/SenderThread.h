/*
 * SenderThread.h
 *
 *  Created on: 28.05.2018
 *      Author: Maxi
 */

#ifndef SRC_SENDERTHREAD_H_
#define SRC_SENDERTHREAD_H_

/* Will try to start the sending thread. NOP when no RTOS is available.*/
void SenderThread_Start();

/* Function will try to enqueue data to the LoRaWAN driver*/
void SenderThread_DoSend();

#endif /* SRC_SENDERTHREAD_H_ */
