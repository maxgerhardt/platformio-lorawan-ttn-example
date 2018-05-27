#include <mbed.h>
#include <lorawan/LoRaWANInterface.h>
#include <SX1276_LoRaRadio.h>
#include <LoRaWANStack.h>
#include <SenderThread.h>

Serial pc(USBTX, USBRX, "debug", 921600);

/*
 * Construct LoRaWAN Radio
 *
 *     SX1276_LoRaRadio(PinName mosi,
                     PinName miso,
                     PinName sclk,
                     PinName nss,
                     PinName reset,
                     PinName dio0,
                     PinName dio1,
                     PinName dio2,
                     PinName dio3,
                     PinName dio4,
                     PinName dio5,
 *
 * or
 *
 *     SX1272_LoRaRadio(PinName mosi,
                     PinName miso,
                     PinName sclk,
                     PinName nss,
                     PinName reset,
                     PinName dio0,
                     PinName dio1,
                     PinName dio2,
                     PinName dio3,
                     PinName dio4,
                     PinName dio5,
                     PinName rf_switch_ctl1 = NC,
                     PinName rf_switch_ctl2 = NC,
                     PinName txctl = NC,
                     PinName rxctl = NC,
                     PinName ant_switch = NC,
                     PinName pwr_amp_ctl = NC,
                     PinName tcxo = NC);
 *
 */

/* comment or uncomment this to use the different radios */
#define USE_SX1276_RADIO

#ifdef USE_SX1276_RADIO
SX1276_LoRaRadio radio(
		SPI_MOSI,
		SPI_MISO,
		SPI_SCK,
		D3,	/* NSS */
		D9,	/* Reset */
		D4,	/* DIO 0 */
		D5,	/* DIO 1 */
		D6,	/* DIO 2 */
		D7,	/* DIO 3 */
		D8,	/* DIO 4 */
		NC	/* DIO 5 */
);
#else
/* taken from the SX1272MB2xAS shield, "Connectivity"
 * https://os.mbed.com/components/SX1272MB2xAS/
 * */
SX1272_LoRaRadio radio(
		D11, /* MOSI */
		D12, /* MISO */
		D13, /* SCK */
		D10, /* NSS */
		A0,	/* (N)Reset */
		D2,	/* DIO 0 */
		D3,	/* DIO 1 */
		D4,	/* DIO 2 */
		D5,	/* DIO 3 */
		NC,	/* DIO 4 */
		NC	/* DIO 5 */
);
#endif

/* construct a LoRaWANInterface object using the radio */
LoRaWANInterface lorawan(radio);

int main() {

	pc.printf("Hello world\n");

	if(LoRaWANStack_Init() < 0) {
		printf("[-] LoRaWAN stack init failed\n");
		return -1;
	} else {
		printf("[+] LoRaWAN stack startup OK\n");
	}

	SenderThread_Start();

	LoRaWANStack_ServeForever();

	//Should never be reached
	return 0;
}

