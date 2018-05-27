#include <SenderThread.h>
#include <mbed.h>
#include <rtos.h>
#include <LoRaWANStack.h>

/* send (queue) something every 10 seconds.
 * actual pushed out data depends on the current SF.
 */
#define SENDER_TX_MILLIS (10 * 1000)

/* thread memory */
uint8_t threadMem[2048];
Thread appThread(osPriorityNormal, sizeof(threadMem), threadMem);

void SenderThread_DoSend() {
	const uint8_t dummyData[] = { 0xAB, 0xCD, 0xEF };
	uint8_t fport = 22;
	//Busy-wait until sending becomes available
	//TODO solve this better with EventFlags after TX_DONE
	//or use the already existing EventQueue like in the example code
	while(LoRaWAN_SendingInProgress()) {
		wait_ms(500);
	}
	LoRaWANStack_Send(fport, dummyData, sizeof(dummyData));
}

void SenderThread_Thread() {
	while (true) {
		SenderThread_DoSend();
		wait_ms(SENDER_TX_MILLIS);
	}
}

void SenderThread_Start() {
	appThread.start(callback(SenderThread_Thread));
}

