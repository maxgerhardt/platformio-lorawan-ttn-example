/*
 * LoRaWANStack.cpp
 *
 *  Created on: 27.05.2018
 *      Author: Maxi
 */

#include <LoRaWANStack.h>
#include "lorawan/LoRaWANInterface.h"
#include "lorawan/system/lorawan_data_structures.h"
#include "lorawan/lorastack/phy/lora_phy_ds.h"
#include "events/EventQueue.h"
#include "main.h" /* for LoRaWAN interface */
#include "Debug.h"
#include <project_settings.h>

using namespace events;

/* Receive buffer of maximum size  */
uint8_t rx_buffer[255];

#define MAX_NUMBER_OF_EVENTS            10
#define CONFIRMED_MSG_RETRY_COUNTER     3

/* event queue */
static EventQueue ev_queue(MAX_NUMBER_OF_EVENTS * EVENTS_EVENT_SIZE);
/* lora app callbacks */
static lorawan_app_callbacks_t callbacks;
/* Receive callback */
static receive_func_t lora_recive_cb = nullptr;
/* is sending flag */
static bool isSending = true; /* until we have a "Connection established" */

/* function prototypes */
static void lora_event_handler(lorawan_event_t event);
static void receive_message();

/* Conversion function from SF number to LoRa stack datarate (DR_0 to DR_5)
 * This is only valid for EU868!!!
 * */
uint8_t ConvertSFToDR(int sf) {
	switch(sf) {
	case 12:
		return DR_0;
	case 11:
		return DR_1;
	case 10:
		return DR_2;
	case 9:
		return DR_3;
	case 8:
		return DR_4;
	case 7:
		return DR_5;
	/* technically in EU868 we also have DR_6 (SF7 BW250). ignore it for now. */
	default:
		return DR_0;
	}
}

bool LoRaWAN_SendingInProgress() {
	return isSending;
}

int LoRaWANStack_Init() {
    // stores the status of a call to LoRaWAN protocol
    lorawan_status_t retcode;

    // Initialize LoRaWAN stack
    if (lorawan.initialize(&ev_queue) != LORAWAN_STATUS_OK) {
        printf("\r\n LoRa initialization failed! \r\n");
        return -1;
    }

    printf("\r\n Mbed LoRaWANStack initialized \r\n");

    // prepare application callbacks
    callbacks.events = mbed::callback(lora_event_handler);
    lorawan.add_app_callbacks(&callbacks);

    // Set number of retries in case of CONFIRMED messages
    if (lorawan.set_confirmed_msg_retries(CONFIRMED_MSG_RETRY_COUNTER)
                                          != LORAWAN_STATUS_OK) {
        printf("\r\n set_confirmed_msg_retries failed! \r\n\r\n");
        return -1;
    }

    printf("\r\n CONFIRMED message retries : %d \r\n",
           CONFIRMED_MSG_RETRY_COUNTER);

    // Enable adaptive data rate
    if (lorawan.enable_adaptive_datarate() != LORAWAN_STATUS_OK) {
        printf("\r\n enable_adaptive_datarate failed! \r\n");
        return -1;
    }

    printf("\r\n Adaptive data  rate (ADR) - Enabled \r\n");

    //Set the initial datarate to use.
    //for EU868, DR_0 = SF12, DR_3 = SF9, DR_5 = SF7
    if(lorawan.set_datarate(ConvertSFToDR(LORA_TX_SF)) != LORAWAN_STATUS_OK) {
        printf("\r\n set_datarate failed! \r\n");
        return -1;
    }
    printf("\r\n Spreading factor set to %d \r\n", LORA_TX_SF);

    retcode = lorawan.connect();

    if (retcode == LORAWAN_STATUS_OK ||
        retcode == LORAWAN_STATUS_CONNECT_IN_PROGRESS) {
    } else {
        printf("\r\n Connection error, code = %d \r\n", retcode);
        return -1;
    }

    printf("\r\n Connection - In Progress ...\r\n");

    return 0;
}

bool LoRaWANStack_Send(uint8_t fport, const uint8_t* data, size_t len, bool confirmed) {
	int16_t retcode = lorawan.send(fport, data, len,
                           confirmed ? MSG_CONFIRMED_FLAG : MSG_UNCONFIRMED_FLAG);

    if (retcode < 0) {
        retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - WOULD BLOCK\r\n")
                : printf("\r\n send() - Error code %d \r\n", retcode);
        return false;
    }

    hexDump("lora tx data", data, len);
    isSending = true;
    return true;
}

void LoRaWANStack_InstallReceiveCB(receive_func_t func) {
	lora_recive_cb = func;
}

void LoRaWANStack_ServeForever() {
    // make your event queue dispatching events forever
    ev_queue.dispatch_forever();
}

/**
 * Event handler
 */
static void lora_event_handler(lorawan_event_t event)
{
    switch (event) {
        case CONNECTED:
            printf("\r\n Connection - Successful \r\n");
            isSending = false;
            break;
        case DISCONNECTED:
            ev_queue.break_dispatch();
            printf("\r\n Disconnected Successfully \r\n");
            break;
        case TX_DONE:
            printf("\r\n Message Sent to Network Server \r\n");
            isSending = false; //free to send again
            break;
        case TX_TIMEOUT:
        case TX_ERROR:
        case TX_CRYPTO_ERROR:
        case TX_SCHEDULING_ERROR:
            printf("\r\n Transmission Error - EventCode = %d \r\n", event);
            break;
        case RX_DONE:
            printf("\r\n Received message from Network Server \r\n");
            receive_message();
            break;
        case RX_TIMEOUT:
        case RX_ERROR:
            printf("\r\n Error in reception - Code = %d \r\n", event);
            break;
        case JOIN_FAILURE:
            printf("\r\n OTAA Failed - Check Keys \r\n");
            break;
        default:
            MBED_ASSERT("Unknown Event");
    }
}

/**
 * Receive a message from the Network Server
 */
static void receive_message()
{
    int16_t retcode;
    //The receive API is a little bit idiotic -- we have to know
    //the received FPort number in advance. Here we just try
    //all possibilities until one is hit.
    for(int fport = 0; fport < 255; fport++) {
		retcode = lorawan.receive(fport, rx_buffer,
								  sizeof(rx_buffer),
								  MSG_CONFIRMED_FLAG|MSG_UNCONFIRMED_FLAG);

		if (retcode < 0) {
			//wrong port, just continue searching..
			//printf("\r\n receive() - Error code %d \r\n", retcode);
			continue;
		}

		hexDump("lora received data", (uint8_t*) rx_buffer, (size_t) retcode);

		if(lora_recive_cb != nullptr) {
			lora_recive_cb((uint8_t*) rx_buffer, (size_t) retcode);
		}

		memset(rx_buffer, 0, sizeof(rx_buffer));
		break;
    }
}
