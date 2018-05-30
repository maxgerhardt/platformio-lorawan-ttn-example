#include <SenderThread.h>
#include <LoRaWANStack.h>
#include <mbed.h>
#include <project_settings.h>

/* the sender function is always there. */
void SenderThread_DoSend() {
	const uint8_t dummyData[] = { 0xAB, 0xCD, 0xEF };
	uint8_t fport = 22;
	LoRaWANStack_Send(fport, dummyData, sizeof(dummyData));
}

/* We only compile this threading stuff if we
 * are runnong with an RTOS. Else we will fall back
 * to a non-threaded variant. */
#ifdef MBED_CONF_RTOS_PRESENT

#include <rtos.h>

/* thread memory */
uint8_t threadMem[2048];
Thread appThread(osPriorityNormal, sizeof(threadMem), threadMem);

static void SenderThread_Thread() {
	while (true) {
		//Busy-wait until sending becomes available
		//TODO solve this better with EventFlags after TX_DONE
		//or use the already existing EventQueue like in the example code
		while(LoRaWAN_SendingInProgress()) {
			wait_ms(500);
		}
		SenderThread_DoSend();
		wait_ms(SENDER_TX_MILLIS);
	}
}

void SenderThread_Start() {
	appThread.start(callback(SenderThread_Thread));
}

#else

void SenderThread_Start() {
	//appThread.start(callback(SenderThread_Thread));
}

#endif
