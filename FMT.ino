#include "VirtualWire.h"
#include "RadioUtil.h"

#define RF433_RECV_PIN 4
#define LED_Y_PIN      12
#define LED_G_PIN      13

void setupRF433()
{
    vw_set_rx_pin(RF433_RECV_PIN);
    vw_setup(2000);
    vw_rx_start();
}

void setup()
{
    Serial.begin(38400);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_Y_PIN, OUTPUT);
    
    digitalWrite(LED_G_PIN, HIGH);
    digitalWrite(LED_Y_PIN, HIGH);

    Serial.println("Setup RF433");
    setupRF433();

    digitalWrite(LED_G_PIN, HIGH);
    digitalWrite(LED_Y_PIN, LOW);
}

void loop()
{
    receiveRF433Data();
    delay(1);
}

void receiveRF433Data()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
        digitalWrite(LED_Y_PIN, true);
	Serial.print("RF433: ");
	
	for (i = 0; i < buflen; i++)
	{
	    Serial.print(buf[i]);
	    Serial.print('\t');
	}
	Serial.println("");
    } else {
        digitalWrite(LED_Y_PIN, false);
    }
}

